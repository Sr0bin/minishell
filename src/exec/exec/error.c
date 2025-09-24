/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 08:10:16 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/24 15:05:35 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(const char *msg, int exit_code)
{
	if (errno)
		perror(msg);
	else
		ft_putstr_fd((char *)msg, 2);
	exit_code_update(exit_code);
}

void	*free_exec(void *exec_data)
{
	if (exec_data == NULL)
		return (NULL);
	close_pipes(exec_data);
	free_envp(((t_exec_data *) exec_data)->envp);
	free_exec_data(exec_data);
	return (NULL);
}

void	ft_fatal_error(void *arg, const char *msg, int exit_code,
	void *(*f)(void *))
{
	if (errno)
		perror(msg);
	else
		ft_putstr_fd((char *)msg, 2);
	f(arg);
	rl_clear_history();
	free(context_read());
	exit(exit_code);
}
