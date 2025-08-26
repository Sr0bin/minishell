/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 08:10:16 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/26 08:10:59 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/multipipes.h"

void	ft_error(t_exec_data *exec_data, const char *msg, int exit_code)
{
	perror(msg);
	free_exec_data(exec_data);
	exit (exit_code);
}
