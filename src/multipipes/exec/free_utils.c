/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:04:52 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/20 14:48:12 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes/multipipes.h"

void	free_cmd(t_cmds *cmd)
{
	int	i;

	i = 0;
	if (cmd->cmd)
	{
		while (cmd->cmd[i])
		{
			free(cmd->cmd[i]);
			i++;
		}
		free(cmd->cmd);
	}
	free(cmd->fd_in.fd);
	free(cmd->fd_out.fd);
}

void	free_cmds(t_utils *utils)
{
	int	i;

	i = 0;
	while (i < utils->nb_cmds)
	{
		free_cmd(&utils->cmds[i]);
		i++;
	}
	free(utils->cmds);
}

void	free_fds(int **fd)
{
	int	i;

	i = 0;
	if (fd)
	{
		while (fd[i])
		{
			free(fd[i]);
			i++;
		}
	}
	free(fd);
}

void	free_utils(t_utils *utils)
{
	if (!utils)
		exit (1);
	if (utils->cmds)
		free_cmds(utils);
	if (utils->fd)
		free_fds(utils->fd);
	free (utils);
}

void	ft_error(t_utils *utils, const char *msg, int exit_code)
{
	perror(msg);
	free_utils(utils);
	exit (exit_code);
}
