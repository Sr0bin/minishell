/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:14:56 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/31 21:34:14 by rorollin         ###   ########.fr       */
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
	apply_redirections(exec_data, i);
	exec_builtins(exec_data, i);
	dup2(tmp_stdin, STDIN_FILENO);
	dup2(tmp_stdout, STDOUT_FILENO);
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
		ft_fatal_error(exec_data, "minishell: fork failed", 1);
	else if (pid == 0)
		exec_cmd(exec_data, i);
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

int	exec_pipex(t_exec_data *exec_data)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	status = 0;
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

static t_exec_data	*exec_data_init(t_ast *ast_root,t_token_list **tkn_lst, t_env *env)
{
	t_exec_data	*exec_data;

	exec_data = ft_calloc(1, sizeof(t_exec_data));
	if (!exec_data)
		ft_fatal_error(exec_data, "minishell: malloc failed", 1);
	*exec_data = (t_exec_data){0};
	exec_data->envp = env;
	exec_data->root = ast_root;
	exec_data->tkn_list = tkn_lst;
	return (exec_data);
}

t_exec_data	*exec_data_context(t_exec_data *ptr, t_exec_data_context flag)
{
	static t_exec_data *exec_data;
	if (flag == SET_EXEC_DATA)
		exec_data = ptr;
	else if (flag == UNSET_EXEC_DATA)
			exec_data = NULL;
	else if (flag == READ_EXEC_DATA)
			return (exec_data);
	return (NULL);
}


int	exec(t_ast *ast_root, t_token_list **tkn_lst, t_env	*env)
{
	t_exec_data	*exec_data;

	exec_data = exec_data_init(ast_root, tkn_lst, env);
	exec_data_context(exec_data, SET_EXEC_DATA);
	ast_to_cmds(exec_data, ast_root);
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
	exec_data_context(NULL, UNSET_EXEC_DATA);
	free_exec_data(exec_data);
	return (0);
}
