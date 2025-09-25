/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:15:44 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/25 12:59:11 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"
#include "context.h"
#include <signal.h>

void	analyze_status(int status)
{
	int	sig;

	if (WIFEXITED(status))
		exit_code_update(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			printf("\n");
		if (sig == SIGQUIT)
			printf("Quit (core dumped)\n");
		exit_code_update(sig + 128);
	}
}

void	wait_cmd(t_exec_data *exec_data)
{
	int		status;
	int		i;
	int		last_pid;
	pid_t	pid;

	i = 0;
	status = 0;
	last_pid = exec_data->pids[exec_data->nb_cmds - 1];
	while (i < exec_data->nb_cmds)
	{
		pid = wait(&status);
		if (pid == -1)
			ft_error("minishell: wait failed\n", 1);
		if (pid == last_pid)
			analyze_status(status);
		i++;
	}
}
