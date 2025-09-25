/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:20:54 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/31 14:20:09 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

int	newline(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	if (ft_strlen(str) == 1)
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_cmds cmd)
{
	int	i;
	int	no_newline;
	int	count;

	no_newline = 0;
	i = 1;
	count = count_nbr_args(cmd.cmd);
	while (cmd.cmd[i] && newline(cmd.cmd[i]))
	{
		no_newline = 1;
		i++;
	}
	while (i < count)
	{
		write(STDOUT_FILENO, cmd.cmd[i], ft_strlen(cmd.cmd[i]));
		if (i < count - 1)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (no_newline == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
