/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:19:01 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/22 11:14:55 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_exit(t_exec_data *exec_data, int exit_code)
{
	int	status;

	status = exit_code;
	printf("exit\n");
	close_tmp_fds(exec_data->fd[0][0], exec_data->fd[0][1]);
	free_envp(exec_data->envp);
	free_exec_data(exec_data);
	rl_clear_history();
	exit (status);
}

int	ft_is_digit_and_sign(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '-' || cmd[i] == '+')
		i++;
	while (cmd[i])
	{
		if ((cmd[i] < '0' || cmd[i] > '9'))
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
		{
			close_tmp_fds(exec_data->fd[0][0], exec_data->fd[0][1]);
			ft_putendl_fd((char *) "exit", 2);
			ft_fatal_error(exec_data,
				"minishell: exit: numeric argument required\n", 2, free_exec);
		}
		else if (count_nbr_args(cmd.cmd) > 2)
		{
			ft_error("minishell: exit: too many arguments\n", 2);
			return (-1);
		}
		else
			handle_exit(exec_data, ft_atoi(cmd.cmd[1]));
	}
	return (0);
}
