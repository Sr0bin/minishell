/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:10:10 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/28 19:06:45 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/multipipes.h"

void	init_pipes(t_exec_data *exec_data)
{
	int	i;

	i = 0;
	exec_data->fd = malloc(sizeof(int *)
			* (long unsigned int)(exec_data->nb_cmds - 1));
	if (!exec_data->fd)
		ft_fatal_error(exec_data, "minishell: malloc", 1);
	while (i < exec_data->nb_cmds - 1)
	{
		exec_data->fd[i] = malloc(sizeof(int) * 2);
		if (!exec_data->fd[i])
			ft_fatal_error(exec_data, "minishell: malloc", 1);
		exec_data->fd[i][0] = -1;
		exec_data->fd[i][1] = -1;
		i++;
	}
}
