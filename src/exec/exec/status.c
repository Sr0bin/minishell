/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:15:44 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/02 17:53:17 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"
#include "context.h"
#include <signal.h>

void	analyze_status(t_exec_data *exec_data, int status)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			printf("\n");
		else if (sig == SIGQUIT)
			printf("Quit (core dumped)\n");

		exit_code_update(WTERMSIG(status) + 128);
	}
	else if (WIFEXITED(status))
		exit_code_update(WEXITSTATUS(status));
}

void	wait_cmd(t_exec_data *exec_data, pid_t pid, int status)
{
	int	i;

	i = 0;
	while (i < exec_data->nb_cmds)
	{
		waitpid(pid, &status, 0);
		analyze_status(exec_data, status);
		i++;
	}
}
