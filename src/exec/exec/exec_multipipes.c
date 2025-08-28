/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multipipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:08:44 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/27 21:13:55 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/multipipes.h"
#include "builtins/builtins.h"
#include <signal.h>

void	close_parent_fds(t_exec_data *exec_data, int i)
{
	if (i > 0)
	{
		close(exec_data->fd[i - 1][0]);
		exec_data->fd[i - 1][0] = -1;
	}
	if (i < exec_data->nb_cmds - 1)
	{
		close(exec_data->fd[i][1]);
		exec_data->fd[i][1] = -1;
	}
}

void	analyze_status(t_exec_data *exec_data, int status)
{
	int sig;

	if (WIFSIGNALED(status))
	{	
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			printf("\n");
		else if (sig == SIGQUIT)
			printf("Quit (core dumped)\n");
		exec_data->exit_code = WTERMSIG(status) + 128;
	}
	else if (WIFEXITED(status))
		exec_data->exit_code = WEXITSTATUS(status);
}

void	exec_pipex(t_exec_data *exec_data)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i < exec_data->nb_cmds)
	{
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
	i = 0;
	while (i < exec_data->nb_cmds)
	{
		waitpid(pid, &status, 0);
		analyze_status(exec_data, status);
		i++;
	}
}
