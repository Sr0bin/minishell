/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:14:56 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/30 11:51:28 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_generation/ast.h"
#include "parsing/token.h"
#include "exec/exec.h"

int	exec_single_cmd(t_exec_data *exec_data, int i)
{
	pid_t	pid;
	int		status;

	if (exec_builtins(exec_data, i) == 0)
		return (0);
	pid = fork();
	if (pid == -1)
		ft_fatal_error(exec_data, "minishell: fork failed", 1);
	else if (pid == 0)
		exec_cmd(exec_data, 0);
	else
	{
		waitpid(pid, &status, 0);
		analyze_status(exec_data, status);
	}
	return (0);
}

int	exec_cmd(t_exec_data *exec_data, int i)
{
	signal_in_child();
	setup_io(exec_data, i);
	close_pipes(exec_data);
	run_builtins(exec_data, i);
	check_path(exec_data, i);
	exec_external(exec_data, i);
	return (0);
}

void	wait_cmd(t_exec_data *exec_data, pid_t pid, int status)
{
	int	i;

	i = 0;
	while (i < exec_data->nb_cmds)
	{
		waitpid(pid, &status, 0);
		analyze_status(exec_data, status);
		i++;
	}
}

int	exec_pipex(t_exec_data *exec_data)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i < exec_data->nb_cmds)
	{
		if (i < exec_data->nb_cmds - 1)
		{
			if (pipe(exec_data->fd[i]) == -1)
				ft_fatal_error(exec_data, "minishell: pipe failed", 1);
		}
		pid = fork();
		if (pid == -1)
			ft_fatal_error(exec_data, "minishell: fork failed", 1);
		else if (pid == 0)
			exec_cmd(exec_data, i);
		else
			close_parent_fds(exec_data, i);
		i++;
	}
	wait_cmd(exec_data, pid, status);
	return (0);
}

int	exec(t_ast *root, t_token_list **tkn_lst, t_env	*env)
{
	t_exec_data	*exec_data;

	exec_data = malloc(sizeof(t_exec_data));
	if (!exec_data)
		ft_fatal_error(exec_data, "minishell: malloc failed", 1);
	*exec_data = (t_exec_data){0};
	exec_data->envp = env;
	exec_data->root = root;
	exec_data->tkn_list = tkn_lst;
	ast_to_cmds(exec_data, root);
	if (exec_data->nb_cmds == 1)
	{
		if ((exec_single_cmd(exec_data, 0)) == 1)
			return (1);
	}
	else
	{
		init_pipes(exec_data);
		exec_pipex(exec_data);
	}
	free_exec_data(exec_data);
	return (0);
}
