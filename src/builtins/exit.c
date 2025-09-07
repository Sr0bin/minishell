/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:19:01 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/07 13:21:03 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_exit(t_exec_data *exec_data, int exit_code)
{
	int	status;

	status = exit_code;
	printf("exit\n");
	free_envp(exec_data->envp);
	free_exec_data(exec_data);
	exit (status);
}

int	ft_is_digit_and_sign(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] < '0' || cmd[i] > '9') && (cmd[i] != '+' && cmd[i] != '-'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(t_exec_data *exec_data, t_cmds cmd)
{
	if (count_nbr_args(cmd.cmd) == 1)
		handle_exit(exec_data, exit_code_read());
	else if (count_nbr_args(cmd.cmd) >= 2)
	{
		if (ft_is_digit_and_sign(cmd.cmd[1]) == 1)
			ft_fatal_error(exec_data, "minishell: exit: numeric argument required", 2, free_exec);
		else if (count_nbr_args(cmd.cmd) > 2)
			printf("minishell: exit: too many arguments\n");
		else
			handle_exit(exec_data, ft_atoi(cmd.cmd[1]));
	}
	return (0);
}
