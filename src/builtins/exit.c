/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:19:01 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/30 14:51:12 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_exit(t_exec_data *exec_data, t_cmds cmd, int exit_code)
{
	int	status;

	status = exit_code;
	printf("exit\n");
	free_envp(exec_data->envp);
	free_exec_data(exec_data);
	exit (status);
}

int	ft_exit(t_exec_data *exec_data, t_cmds cmd)
{
	int	status;

	if (count_nbr_args(cmd.cmd) == 1)
		handle_exit(exec_data, cmd, exec_data->exit_code);
	else if (count_nbr_args(cmd.cmd) == 2)
	{
		if (ft_atoi(cmd.cmd[1]) != 0)
			handle_exit(exec_data, cmd, ft_atoi(cmd.cmd[1]));
		else
			ft_error(exec_data, "minishell: wrong scope of arguments", 2);
	}
	else if (count_nbr_args(cmd.cmd) > 2)
		printf("minishell: exit: too many arguments\n");
	return (0);
}
