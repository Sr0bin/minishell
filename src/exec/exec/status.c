/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:15:44 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/30 11:52:15 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"
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
		exec_data->exit_code = WTERMSIG(status) + 128;
	}
	else if (WIFEXITED(status))
		exec_data->exit_code = WEXITSTATUS(status);
}
