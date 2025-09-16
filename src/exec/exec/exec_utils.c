/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:37:42 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/16 10:38:38 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_tmp_fds(int fd_in, int fd_out)
{
	close(fd_in);
	close(fd_out);
}

void	restore_fds(t_exec_data *exec_data)
{
	dup2(exec_data->fd[0][0], STDIN_FILENO);
	dup2(exec_data->fd[0][1], STDOUT_FILENO);
	close_tmp_fds(exec_data->fd[0][0], exec_data->fd[0][1]);
}

void	cleanup(t_exec_data *exec_data)
{
	int	i;

	i = 0;
	while (i < exec_data->nb_cmds - 1)
	{
		if (exec_data->fd[i][0] != -1)
			close(exec_data->fd[i][0]);
		if (exec_data->fd[i][1] != -1)
			close(exec_data->fd[i][1]);
		exec_data->fd[i][0] = -1;
		exec_data->fd[i][1] = -1;
		i++;
	}
	i = 0;
	while (i < exec_data->nb_cmds)
	{
		if (exec_data->pids[i] != -1)
		{
			kill(exec_data->pids[i], SIGKILL);
			waitpid(exec_data->pids[i], NULL, 0);
		}
		i++;
	}
}
