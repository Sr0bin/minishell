/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:35:05 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/30 11:44:00 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

#include "../exec/structs.h"

void	setup_signals(void);
void	handler_signals(int signum);
void	analyze_status(t_exec_data *exec_data, int status);

# endif