/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:14:56 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/04 15:52:34 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_generation/ast.h"
#include "parsing/token.h"
#include "exec/exec.h"

int	exec_single_builtin(t_exec_data *exec_data, int i)
{
	int	tmp_stdin;
	int	tmp_stdout;

	tmp_stdin = dup(STDIN_FILENO);
	tmp_stdout = dup(STDOUT_FILENO);
	if (tmp_stdin == -1 || tmp_stdout == -1)
		ft_fatal_error(exec_data, "error retrieving current directory", 2, free_exec);
	apply_redirections(exec_data, i);
	if (exec_builtins(exec_data, i) == -1)
	//lose + ft_error
	if ((dup2(tmp_stdin, STDIN_FILENO)) == -1)
		ft_fatal_error(exec_data, "dup2 failed", 2, free_exec);
	if ((dup2(tmp_stdout, STDOUT_FILENO)) == -1)
		ft_fatal_error(exec_data, "dup2 failed", 2, free_exec);
	close(tmp_stdin);
	close(tmp_stdout);
	return (0);
}

int	exec_single_cmd(t_exec_data *exec_data, int i)
{
	pid_t			pid;
	int				status;

	if (is_builtin(exec_data->cmds->cmd[0]))
	{
		exec_single_builtin(exec_data, i);
		return (0);
	}
	pid = fork();
	if (pid == -1)
		ft_fatal_error(exec_data, "fork failed", 1, &free_exec);
	else if (pid == 0)
		exec_cmd(exec_data, i);
	else
	{
		waitpid(pid, &status, 0);
		analyze_status(status);
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
				ft_fatal_error(exec_data, "pipe failed", 1, &free_exec);
		}
		pid = fork();
		if (pid == -1)
			ft_fatal_error(exec_data, "fork failed", 1, &free_exec);
		else if (pid == 0)
			exec_cmd(exec_data, i);
		else
			close_parent_fds(exec_data, i);
		i++;
	}
	wait_cmd(exec_data);
	return (0);
}

int	 exec(t_ast *root, t_token_list **tkn_lst, t_env *env)
{
	t_exec_data	*exec_data;

	if (!root)
		return (1);
	exec_data = malloc(sizeof(t_exec_data));
	if (!exec_data)
		ft_fatal_error(exec_data, "malloc failed", 1, &free_exec);
	*exec_data = (t_exec_data){0};
	exec_data->envp = env;
	exec_data->root = root;
	exec_data->tkn_list = tkn_lst;
	if (ast_to_cmds(exec_data, root) == 1)
		return (1);
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
