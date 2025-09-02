/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 08:10:16 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/03 01:34:24 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(const char *msg, int exit_code)
{
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putendl_fd((char *)msg, STDOUT_FILENO);
	exit_code_update(exit_code);
}

void	*free_exec(void *exec_data)
{
	if (exec_data == NULL)
		return (NULL);
	free_envp(((t_exec_data *) exec_data)->envp);
	free_exec_data(exec_data);
	return (NULL);
}

void	ft_fatal_error(void *arg, const char *msg, int exit_code, void *(*f)(void *))
{
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putendl_fd((char *)msg, STDOUT_FILENO);
	f(arg);
	exit (exit_code);
}
