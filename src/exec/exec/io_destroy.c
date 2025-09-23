/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:02:34 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/23 14:25:39 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	io_free(t_exec_data *exec_data)
{
	close_pipes(exec_data);
	ft_fatal_error(exec_data, "minishell: dup2 failed\n",
		1, &free_exec);
}

int	setup_io(t_exec_data *exec_data, int i)
{
	int	exit_code;

	if (i > 0)
	{
		if (dup2(exec_data->fd[i - 1][0], STDIN_FILENO) == -1)
			io_free(exec_data);
	}
	if (i < exec_data->nb_cmds - 1)
	{
		if (dup2(exec_data->fd[i][1], STDOUT_FILENO) == -1)
			io_free(exec_data);
	}
	if (apply_redirections(exec_data, i) == -1)
	{
		exit_code = exit_code_read();
		close_pipes(exec_data);
		free_exec(exec_data);
		free(context_read());
		exit(exit_code);
	}
	return (0);
}
