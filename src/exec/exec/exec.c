/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:14:56 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/08 18:32:37 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_generation/ast.h"
#include "parsing/token.h"
#include "exec/exec.h"
#include "context.h"

static void	close_tmp_fds(int fd_in, int fd_out)
{
	close(fd_in);
	close(fd_out);
}

void	restore_fds(t_exec_data *exec_data)
{
	dup2(exec_data->fd[0][0], STDIN_FILENO);
	dup2(exec_data->fd[0][1], STDOUT_FILENO);
	close_tmp_fds(exec_data->fd[0][0], exec_data->fd[0][1]);
}

int	exec_single_builtin(t_exec_data *exec_data, int i)
{
	exec_data->fd = malloc(sizeof(int *));
	if (!exec_data->fd)
		ft_fatal_error(exec_data, "minishell: malloc failed", 1, &free_exec);
	exec_data->fd[0] = malloc(sizeof(int) * 2);
	if (!exec_data->fd[0])
		ft_fatal_error(exec_data, "minishell: malloc failed", 1, &free_exec);
	exec_data->fd[0][0] = dup(STDIN_FILENO);
	exec_data->fd[0][1] = dup(STDOUT_FILENO);
	if (exec_data->fd[0][0] == -1 || exec_data->fd[0][1] == -1)
	{
		close(exec_data->fd[0][0]);
		close(exec_data->fd[0][1]);
		ft_fatal_error(exec_data, "minishell: dup failed", 1, &free_exec);
	}
	if (apply_redirections(exec_data, i) == -1)
	{
		restore_fds(exec_data);
		return (-1);
	}
	if (exec_builtins(exec_data, i) == -1)
	{
		restore_fds(exec_data);
		return (-1);
	}
	if ((dup2(exec_data->fd[0][0], STDIN_FILENO)) == -1)
	{
		close_tmp_fds(exec_data->fd[0][0],exec_data->fd[0][1]);
		ft_fatal_error(exec_data, "minishell: dup2 failed", 2, &free_exec);
	}
	if ((dup2(exec_data->fd[0][1], STDOUT_FILENO)) == -1)
	{
		close_tmp_fds(exec_data->fd[0][0],exec_data->fd[0][1]);
		ft_fatal_error(exec_data, "minishell: dup2 failed", 2, &free_exec);
	}
	close_tmp_fds(exec_data->fd[0][0], exec_data->fd[0][1]);
	return (0);
}

int	exec_single_cmd(t_exec_data *exec_data, int i)
{
	pid_t			pid;
	int				status;

	if (is_builtin(exec_data->cmds->cmd[0]))
	{
		if (exec_single_builtin(exec_data, i) == -1)
			return (-1);
		return (0);
	}
	pid = fork();
	if (pid == -1)
		ft_fatal_error(exec_data, "minishell: fork failed", 1, &free_exec);
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

int	exec_pipex(t_exec_data *exec_data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < exec_data->nb_cmds)
	{
		if (i < exec_data->nb_cmds - 1)
		{
			if (pipe(exec_data->fd[i]) == -1)
				ft_fatal_error(exec_data, "minishell: pipe failed", 1, &free_exec);
		}
		pid = fork();
		if (pid == -1)
			ft_fatal_error(exec_data, "minishell: fork failed", 1, &free_exec);
		else if (pid == 0)
			exec_cmd(exec_data, i);
		else
			close_parent_fds(exec_data, i);
		i++;
	}
	wait_cmd(exec_data);
	return (0);
}

int	 exec(t_ast *root)
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
		//TODO: free token_list_from parsing
		ft_fatal_error(NULL, "minishell: malloc failed", 1, NULL);
	}
	ast_to_cmds(exec_data, root);
	if (exec_data->nb_cmds == 1)
	{
		exec_single_cmd(exec_data, 0);
	}
	else
	{
		init_pipes(exec_data);
		exec_pipex(exec_data);
	}
	free_exec_data(exec_data);
	return (0);
}
