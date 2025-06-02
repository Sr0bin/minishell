/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:10:10 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/02 16:16:30 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/multipipes.h"

void	close_pipes(t_utils *utils)
{
	int	i;

	i = 0;
	while (i < utils->nb_cmds - 1)
	{
		if (utils->fd[i][0] > 1)
			close(utils->fd[i][0]);
		if (utils->fd[i][1] > 1)
			close(utils->fd[i][1]);
		i++;
	}
}

void	init_pipes(t_utils *utils)
{
	int	i;

	i = 0;
	utils->fd = malloc(sizeof(int *) * (long unsigned int)(utils->nb_cmds));
	if (!utils->fd)
		ft_error(utils, "Error : malloc failed", 1);
	while (i < utils->nb_cmds - 1)
	{
		utils->fd[i] = malloc(sizeof(int) * 2);
		if (!utils->fd[i])
			ft_error(utils, "Error : malloc failed", 1);
		utils->fd[i][0] = -1;
		utils->fd[i][1] = -1;
		i++;
	}
	utils->fd[i] = NULL;
}
