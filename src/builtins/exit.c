/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:19:01 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/25 18:41:37 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "multipipes/multipipes.h"

int	ft_exit(t_exec_data *exec_data)
{
	int status;

	status = exec_data->status;
	ft_printf("exit\n");
	free_envp(exec_data->envp);
	free_exec_data(exec_data);
	exit(status);
}