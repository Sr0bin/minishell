/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 17:18:02 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/26 08:01:58 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

int	exec_builtins(t_exec_data *exec_data, int i)
{
	if (!ft_strcmp(exec_data->cmds[i].cmd[0], "cd"))
		return (ft_cd(exec_data, exec_data->cmds[i]));
	else if (!ft_strcmp (exec_data->cmds[i].cmd[0], "echo"))
		return (ft_echo(exec_data->cmds[i]));
	else if (!ft_strcmp (exec_data->cmds[i].cmd[0], "env"))
		return (ft_env(exec_data->envp));
	else if (!ft_strcmp(exec_data->cmds[i].cmd[0], "export"))
		return (ft_export(exec_data, exec_data->cmds[i]));
	else if (!ft_strcmp(exec_data->cmds[i].cmd[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(exec_data->cmds[i].cmd[0], "exit"))
		return (ft_exit(exec_data));
	else if (!ft_strcmp(exec_data->cmds[i].cmd[0], "unset"))
		return (ft_unset(&exec_data->envp, exec_data->cmds[i]));
	return (-1);
}
