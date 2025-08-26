/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:42:31 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/26 16:55:36 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>

volatile	sig_atomic_t	g_received_signal = 0; 

void	handler_signals(int signum)
{
	g_received_signal = signum;
	if (signum == SIGINT)
	{
		rl_done = 1;
	}
}

int		nonnull(void)
{
	return (1);
}

void	setup_signals(void)
{
	rl_event_hook = nonnull;
	signal(SIGINT, handler_signals);
	signal(SIGQUIT, SIG_IGN);
}