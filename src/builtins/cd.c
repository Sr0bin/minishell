/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:49:30 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/20 13:26:05 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

int	ft_cd(t_cmds *cmd)
{
	char	*path;
	int		count;

	count = count_nbr_args(cmd->cmd);
	if (count == 1)
	{
		path = getenv("HOME");
		if (!path || chdir(path) == -1)
			perror("minishell: cd");
	}
	else
	{
		path = cmd->cmd[1];
		if (chdir(path) == -1)
			perror("minishell: cd");
	}
	return (1);
}
