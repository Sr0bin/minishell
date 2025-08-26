/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:49:30 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/26 08:02:54 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

int	ft_cd(t_exec_data *exec_data, t_cmds cmd)
{
	char	*path;
	int		count;

	count = count_nbr_args(cmd.cmd);
	if (count == 1)
	{
		path = getenv("HOME");
		if (!path || chdir(path) == -1)
			ft_error(exec_data, "minishell: cd", 1);
	}
	else
	{
		path = cmd.cmd[1];
		if (chdir(path) == -1)
			ft_error(exec_data, "minishell: cd", 1);
	}
	return (1);
}
