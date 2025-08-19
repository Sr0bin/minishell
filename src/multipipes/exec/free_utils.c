/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:04:52 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/19 14:58:59 by lserodon         ###   ########.fr       */
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
}

void	free_cmds(t_exec_data *utils)
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

void	free_exec_data(t_exec_data *exec_data)
{
	if (!exec_data)
		exit (1);
	if (exec_data->cmds)
		free_cmds(exec_data);
	if (exec_data->fd)
		free_fds(exec_data->fd);
	free (exec_data);
}

void	ft_error(t_exec_data *exec_data, const char *msg, int exit_code)
{
	perror(msg);
	free_exec_data(exec_data);
	exit (exit_code);
}
