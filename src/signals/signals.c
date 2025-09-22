/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:42:31 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/30 16:01:36 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals/signals.h"

volatile sig_atomic_t	g_received_signal = 0;

void	handler_signals(int signum)
{
	g_received_signal = signum;
	if (signum == SIGINT)
	{
		rl_done = 1;
	}
}

void	signal_in_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	nonnull(void)
{
	return (1);
}

void	setup_signals(void)
{
	g_received_signal = 0;
	rl_event_hook = nonnull;
	signal(SIGINT, handler_signals);
	signal(SIGQUIT, SIG_IGN);
}
