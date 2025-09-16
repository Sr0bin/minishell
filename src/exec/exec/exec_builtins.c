/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:49:05 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/16 13:58:39 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"

void	init_fds(t_exec_data *exec_data)
{
	exec_data->fd = malloc(sizeof(int *));
	if (!exec_data->fd)
		ft_fatal_error(exec_data, "minishell: malloc failed\n", 1, &free_exec);
	exec_data->fd[0] = malloc(sizeof(int) * 2);
	if (!exec_data->fd[0])
		ft_fatal_error(exec_data, "minishell: malloc failed\n", 1, &free_exec);
	exec_data->fd[0][0] = dup(STDIN_FILENO);
	exec_data->fd[0][1] = dup(STDOUT_FILENO);
	if (exec_data->fd[0][0] == -1 || exec_data->fd[0][1] == -1)
	{
		close(exec_data->fd[0][0]);
		close(exec_data->fd[0][1]);
		ft_fatal_error(exec_data, "minishell: dup failed\n", 1, &free_exec);
	}
}

void	close_dup2_builtins(t_exec_data *exec_data)
{
	if ((dup2(exec_data->fd[0][0], STDIN_FILENO)) == -1)
	{
		close_tmp_fds(exec_data->fd[0][0], exec_data->fd[0][1]);
		ft_fatal_error(exec_data, "minishell: dup2 failed\n", 2, &free_exec);
	}
	if ((dup2(exec_data->fd[0][1], STDOUT_FILENO)) == -1)
	{
		close_tmp_fds(exec_data->fd[0][0], exec_data->fd[0][1]);
		ft_fatal_error(exec_data, "minishell: dup2 failed\n", 2, &free_exec);
	}
	close_tmp_fds(exec_data->fd[0][0], exec_data->fd[0][1]);
}

int	exec_single_builtin(t_exec_data *exec_data, int i)
{
	init_fds(exec_data);
	if (apply_redirections(exec_data, i) == -1)
	{
		restore_fds(exec_data);
		return (-1);
	}
	if (exec_builtins(exec_data, i) == -1)
	{
		restore_fds(exec_data);
		return (-1);
	}
	close_dup2_builtins(exec_data);
	return (0);
}
