/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:19:02 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/17 09:56:03 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/exec.h"

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	free_utils(t_cmd *cmd)
{
	if (cmd->cmd)
		free_cmd(cmd->cmd);
	if (cmd->fd_in.fd)
		free(cmd->fd_in.fd);
	if (cmd->fd_out.fd)
		free(cmd->fd_out.fd);
	free(cmd);
}

void	ft_error(t_cmd *cmd, const char *msg, int exit_code)
{
	perror(msg);
	free_utils(cmd);
	exit (exit_code);
}
