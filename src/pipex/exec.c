/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:08:44 by lserodon          #+#    #+#             */
/*   Updated: 2025/05/15 17:09:06 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_first_cmd(t_utils *utils)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		dup2(utils->infile, STDIN_FILENO);
		dup2(utils->fd[0][1], STDOUT_FILENO);
		close_fds(utils);
		utils->path = find_path(utils->envp, utils->cmds[0]);
		if (execve(utils->path, utils->cmds[0], utils->envp) == -1)
		{
			free_all(utils);
			exit(1);
		}
	}
}

void	exec_mid_cmd(t_utils *utils, int i)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		dup2(utils->fd[i - 1][0], STDIN_FILENO);
		dup2(utils->fd[i][1], STDOUT_FILENO);
		close_fds(utils);
		utils->path = find_path(utils->envp, utils->cmds[i]);
		if (execve(utils->path, utils->cmds[i], utils->envp) == -1)
		{
			free_all(utils);
			exit(1);
		}
	}
}

void	exec_last_cmd(t_utils *utils, int i)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		dup2(utils->fd[i - 1][0], STDIN_FILENO);
		dup2(utils->outfile, STDOUT_FILENO);
		close_fds(utils);
		utils->path =find_path(utils->envp, utils->cmds[utils->nb_commands - 1]);
		if (execve(utils->path, utils->cmds[i], utils->envp) == -1)
		{
			free_all(utils);
			exit(1);
		}
	}
}

void	exec_pipex(t_utils *utils)
{
	int	i;

	i = 0;
	while (i < utils->nb_commands)
	{
		if (i == 0)
			exec_first_cmd(utils);
		else if (i == utils->nb_commands - 1)
			exec_last_cmd(utils, i);
		else
			exec_mid_cmd(utils, i);
		i++;
	}
	while (wait(NULL) > 0)
	;
}
