/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:08:44 by lserodon          #+#    #+#             */
/*   Updated: 2025/05/25 11:29:30 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

void	exec_cmd(t_utils *utils, int i)
{
	int		fd_in;
	int		fd_out;

	fd_in = -1;
	fd_out = -1;
	if (utils->cmds[i].fd_in)
	{
		fd_in = open(utils->cmds[i].fd_in, O_RDONLY);
		if (fd_in < 0)
			perror("fd_in");
		dup2(fd_in, STDIN_FILENO);
	}
	else if (i > 0)
		dup2(utils->fd[i - 1][0], STDIN_FILENO);
	if (utils->cmds[i].fd_out)
	{	
		fd_out = open(utils->cmds[i].fd_out, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd_out < 0)
			perror("fd_out");
		dup2(fd_out, STDOUT_FILENO);
	}
	else if (i < utils->nb_cmds - 1)
		dup2(utils->fd[i][1], STDOUT_FILENO);
	if (fd_in > 2)
		close(fd_in);
	if (fd_out > 2)
		close(fd_out);
	close_all_fds(utils);
	utils->cmds[i].path = find_path(utils->envp, utils->cmds[i].cmd[0]);
	if (execve(utils->cmds[i].path, utils->cmds[i].cmd, utils->envp) == -1)
	{
		perror("execve");
		exit (EXIT_FAILURE);
	}
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
			if(pipe(utils->fd[i]) == -1)
				perror("pipe");
		}
		pid = fork();
		if (pid == 0)
			exec_cmd(utils, i);
		else
		{
			if (i > 0)
				close(utils->fd[i - 1][0]);
			if (i < utils->nb_cmds - 1)
				close(utils->fd[i][1]);
		}
		i++;
	}
	while (wait(NULL) > 0)
	;
}
