/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:14:56 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/22 11:08:26 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_generation/ast.h"
#include "parsing/token.h"
#include "exec/exec.h"
#include "context.h"

int	exec_single_cmd(t_exec_data *exec_data, int i)
{
	pid_t			pid;
	int				status;

	status = 0;
	if (is_builtin(exec_data->cmds->cmd[0]) == 1)
	{
		if (exec_single_builtin(exec_data, i) == -1)
			return (-1);
		return (0);
	}
	pid = fork();
	if (pid == -1)
		ft_fatal_error(exec_data, "minishell: fork failed\n", 1, &free_exec);
	else if (pid == 0)
		exec_cmd(exec_data, i);
	else
	{
		waitpid(pid, &status, 0);
		analyze_status(status);
	}
	return (0);
}

void	exec_cmd(t_exec_data *exec_data, int i)
{
	signal_in_child();
	setup_io(exec_data, i);
	close_pipes(exec_data);
	run_builtins(exec_data, i);
	check_path(exec_data, i);
	exec_external(exec_data, i);
}

int	open_pipe(t_exec_data *exec_data, int i)
{
	if (i < exec_data->nb_cmds - 1)
	{
		if (pipe(exec_data->fd[i]) == -1)
			ft_fatal_error(exec_data, "minishell: pipe failed\n",
				1, &free_exec);
	}
	return (0);
}

int	exec_pipex(t_exec_data *exec_data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < exec_data->nb_cmds)
	{
		open_pipe(exec_data, i);
		pid = fork();
		if (pid == -1)
		{
			cleanup(exec_data);
			ft_fatal_error(exec_data, "minishell: fork failed\n",
				1, &free_exec);
		}
		else if (pid == 0)
			exec_cmd(exec_data, i);
		else
		{
			exec_data->pids[i] = pid;
			close_parent_fds(exec_data, i);
		}
		i++;
	}
	wait_cmd(exec_data);
	return (0);
}

int	exec(t_ast *root)
{
	t_exec_data	*exec_data;
	t_context	*context;

	context = context_read();
	if (!root)
		return (1);
	exec_data = malloc(sizeof(t_exec_data));
	if (!exec_data)
	{
		free_envp(context->env);
		ast_destroy(&root);
		ft_fatal_error(NULL, "minishell: malloc failed\n", 1, NULL);
	}
	ast_to_cmds(exec_data, root);
	if (exec_data->nb_cmds == 1)
		exec_single_cmd(exec_data, 0);
	else
	{
		init_pipes(exec_data);
		exec_pipex(exec_data);
	}
	free_exec_data(exec_data);
	return (0);
}
