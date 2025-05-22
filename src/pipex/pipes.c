/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:10:10 by lserodon          #+#    #+#             */
/*   Updated: 2025/05/21 14:24:56 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
void	close_fds(t_utils *utils)
{
	int	i;

	i = 0;
	while(i < utils->nb_commands - 1)
	{
		if (utils->fd[i][0] >= 0)
			close(utils->fd[i][0]);
		if (utils->fd[i][1] >= 0)
			close(utils->fd[i][1]);
		i++;
	}
	if (utils->infile >= 0)
		close(utils->infile);
	if (utils->outfile >= 0)
		close(utils->outfile);
}

void	init_pipes(t_utils *utils)
{
	int	i;

	i = 0;
	utils->fd = malloc(sizeof(int *) * utils->nb_commands);
	if (!utils->fd)
		return ;
	while(i < utils->nb_commands) 
	{
		utils->fd[i] = malloc(sizeof(int) * 2);
		if (!utils->fd[i])
			return ;
		i++;
	}
}*/
