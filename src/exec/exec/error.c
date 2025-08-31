/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 08:10:16 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/31 21:41:15 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"

void	ft_error(t_exec_data *exec_data, const char *msg, int exit_code)
{
	perror(msg);
	if (exec_data != NULL)
		exec_data->exit_code = exit_code;
}

void	ft_fatal_error(t_exec_data *exec_data, const char *msg, int exit_code)
{
	perror(msg);
	if (exec_data != NULL)
	{
		free_envp(exec_data->envp);
		free_exec_data(exec_data);
	}
	exit (exit_code);
}
