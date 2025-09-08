/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:10:10 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/08 18:25:53 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"

void	close_pipes(t_exec_data *exec_data)
{
	int	j;

	j = 0;
	if (exec_data->nb_cmds == 1)
	{
		if (exec_data->fd[0][0] >= 0)
		close(exec_data->fd[0][0]);
		if (exec_data->fd[0][1] >= 0)
		close(exec_data->fd[0][1]);
	}
	else
	{	
		while (j < exec_data->nb_cmds - 1)
		{
			if (exec_data->fd[j][0] >= 0)
			close(exec_data->fd[j][0]);
			if (exec_data->fd[j][1] >= 0)
			close(exec_data->fd[j][1]);
			j++;
		}
	}
}

void	init_pipes(t_exec_data *exec_data)
{
	int	i;

	i = 0;
	exec_data->fd = malloc(sizeof(int *)
			* (long unsigned int)(exec_data->nb_cmds - 1));
	if (!exec_data->fd)
		ft_fatal_error(exec_data, "minishell: malloc failed", 1, &free_exec);
	while (i < exec_data->nb_cmds - 1)
	{
		exec_data->fd[i] = malloc(sizeof(int) * 2);
		if (!exec_data->fd[i])
			ft_fatal_error(exec_data, "minishell: malloc failed", 1, &free_exec);
		exec_data->fd[i][0] = -1;
		exec_data->fd[i][1] = -1;
		i++;
	}
}
