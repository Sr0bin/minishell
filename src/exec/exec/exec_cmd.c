/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 07:58:00 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/27 16:28:09 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/multipipes.h"
#include <signal.h>

void	exec_single_cmd(t_exec_data *exec_data, int i)
{
	pid_t	pid;
	int 	status;
	
	if(exec_builtins(exec_data, i) != -1)
		return ;
	pid = fork();
	if (pid == -1)
		ft_error(exec_data, "minishell: fork failed", 1);
	else if (pid == 0)
		exec_cmd(exec_data, 0);
	else
	{
		waitpid(pid, &status, 0);
		analyze_status(exec_data, status);
	}
}

int	apply_redirections(t_exec_data *exec_data, int i)
{
	int		fd;
	t_list	*node;
	t_redir	*redir;

	fd = -1;
	node = exec_data->cmds[i].redir;
	while (node)
	{
		redir = (t_redir *)node->content;
		if (redir->type == REDIR_OUTPUT)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == REDIR_APPEND)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == REDIR_INPUT || redir->type == REDIR_HEREDOC)
			fd = open(redir->filename, O_RDONLY);
		if (fd < 0)
			return (-1);
		if (redir->type == REDIR_INPUT)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close (fd);
		node = node->next;
	}
	return (0);
}

void	signal_in_child()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	exec_cmd(t_exec_data *exec_data, int i)
{
	int		j;
	char	**env;

	signal_in_child();
	if (apply_redirections(exec_data, i) < 0)
		ft_error(exec_data, "minishell: no such file or directory", 1);
	if (i > 0)
		dup2(exec_data->fd[i - 1][0], STDIN_FILENO);
	if (i < exec_data->nb_cmds - 1)
		dup2(exec_data->fd[i][1], STDOUT_FILENO);
	j = 0;
	while (j < exec_data->nb_cmds - 1)
	{
		if (exec_data->fd[j][0] >= 0)
			close(exec_data->fd[j][0]);
		if (exec_data->fd[j][1] >= 0)
			close(exec_data->fd[j][1]);
		j++;
	}
	if (exec_builtins(exec_data, i) != -1)
	{
		free_exec_data(exec_data);
		exit(0);
	}
	exec_data->cmds[i].path = find_path(exec_data, i);
	if (!exec_data->cmds[i].path)
		ft_error(exec_data, "minishell: command not found", 127);
	env = t_env_to_array(exec_data);
	if (execve(exec_data->cmds[i].path, exec_data->cmds[i].cmd,
			env) == -1)
		ft_error(exec_data, "minishell: execve failed", 1);
}
