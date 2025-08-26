/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multipipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:08:44 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/26 08:06:27 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/multipipes.h"
#include "builtins/builtins.h"

void	close_parent_fds(t_exec_data *exec_data, int i)
{
	if (i > 0)
		close(exec_data->fd[i - 1][0]);
	if (i < exec_data->nb_cmds - 1)
		close(exec_data->fd[i][1]);
}

void	wait_for_children(t_exec_data *exec_data)
{
	int	i;

	i = 0;
	while (i < exec_data->nb_cmds)
	{
		wait(NULL);
		i++;
	}
}

void	exec_pipex(t_exec_data *exec_data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < exec_data->nb_cmds)
	{
		if (exec_builtins(exec_data, i) == 1)
			return ;
		if (i < exec_data->nb_cmds - 1)
		{
			if (pipe(exec_data->fd[i]) == -1)
				ft_error(exec_data, "minishell: pipe failed", 1);
		}
		pid = fork();
		if (pid == -1)
			ft_error(exec_data, "minishell: fork failed", 1);
		else if (pid == 0)
			exec_cmd(exec_data, i);
		else
			close_parent_fds(exec_data, i);
		i++;
	}
	wait_for_children(exec_data);
}
