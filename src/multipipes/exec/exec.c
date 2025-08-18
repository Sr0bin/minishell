/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:08:44 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/23 13:31:09 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes/multipipes.h"

int	set_input_fd(t_utils *utils, int i)
{
	int	fd_in;

	fd_in = -1;
	if (utils->cmds[i].fd_in.fd)
	{
		fd_in = open(utils->cmds[i].fd_in.fd, O_RDONLY);
		if (fd_in < 0)
			ft_error(utils, "minishell: fd_in failed", 1);
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			close(fd_in);
			ft_error(utils, "minishell: dup2 failed", 1);
		}
	}
	else if (i > 0)
	{
		if (dup2(utils->fd[i - 1][0], STDIN_FILENO) == -1)
			ft_error(utils, "minishell: dup2 failed", 1);
	}
	return (fd_in);
}

int	set_output_fd(t_utils *utils, int i)
{
	int	fd_out;

	fd_out = -1;
	if (utils->cmds[i].fd_out.fd)
	{
		if (utils->cmds[i].fd_out.redir_type == REDIR_APPEND)
			fd_out = open(utils->cmds[i].fd_out.fd,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (utils->cmds[i].fd_out.redir_type == REDIR_OUTPUT)
			fd_out = open(utils->cmds[i].fd_out.fd,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
			ft_error(utils, "minishell : open failed", 1);
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			close(fd_out);
			ft_error(utils, "minishell : dup2 failed", 1);
		}
	}
	else if (i < utils->nb_cmds - 1)
	{
		if (dup2(utils->fd[i][1], STDOUT_FILENO) == -1)
			ft_error(utils, "minishell : dup2 failed", 1);
	}
	return (fd_out);
}

void	exec_cmd(t_utils *utils, int i)
{
	int		fd_in;
	int		fd_out;

	fd_in = set_input_fd(utils, i);
	fd_out = set_output_fd(utils, i);
	if (fd_in > 2)
		close(fd_in);
	if (fd_out > 2)
		close(fd_out);
	close_pipes(utils);
	utils->cmds[i].path = find_path(utils);
	if (!utils->cmds[i].path)
		ft_error(utils, "minishell: command not found", 127);
	if (execve(utils->cmds[i].path, utils->cmds[i].cmd, utils->envp) == -1)
		ft_error(utils, "minishell : execve failed", 1);
}

void	close_parent_fds(t_utils *utils, int i)
{
	if (i > 0)
		close(utils->fd[i - 1][0]);
	if (i < utils->nb_cmds - 1)
		close(utils->fd[i][1]);
}

void	exec_pipex(t_utils *utils)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < utils->nb_cmds)
	{
		if (i < utils->nb_cmds - 1)
		{
			if (pipe(utils->fd[i]) == -1)
				ft_error(utils, "minishell: pipe failed", 1);
		}
		pid = fork();
		if (pid == -1)
			ft_error(utils, "minishell: fork failed", 1);
		else if (pid == 0)
			exec_cmd(utils, i);
		else
			close_parent_fds(utils, i);
		i++;
	}
	while (wait(NULL) > 0)
		;
	free_utils(utils);
	exit (0);
}
