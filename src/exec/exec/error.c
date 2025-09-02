/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 08:10:16 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/02 17:54:37 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(const char *msg, int exit_code)
{
	t_context	*context;

	context = context_set(NULL, READ);
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putendl_fd((char *)msg, STDOUT_FILENO);
	exit_code_update(exit_code);
}

void	ft_fatal_error(t_exec_data *exec_data, const char *msg, int exit_code)
{
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putendl_fd((char *)msg, STDOUT_FILENO);
	free_envp(exec_data->envp);
	free_exec_data(exec_data);
	exit (exit_code);
}
