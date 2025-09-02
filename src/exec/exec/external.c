/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:16:49 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/03 01:26:13 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"

void	check_path(t_exec_data *exec_data, int i)
{
	if (exec_data->cmds[i].cmd[0][0] == '/' ||
			exec_data->cmds[i].cmd[0][0] == '.')
	{
		if (access(exec_data->cmds[i].cmd[0], F_OK) != 0)
			ft_fatal_error(exec_data, "minishell", 127, &free_exec);
		if (access(exec_data->cmds[i].cmd[0], X_OK) != 0)
			ft_fatal_error(exec_data, "minishell", 126, &free_exec);
		exec_data->cmds[i].path = exec_data->cmds[i].cmd[0];
	}
	else
	{
		exec_data->cmds[i].path = find_path(exec_data, i);
		if (!exec_data->cmds[i].path)
			ft_fatal_error(exec_data, "minishell: command not found", 127, &free_exec);
	}
}

void	exec_external(t_exec_data *exec_data, int i)
{
	char	**env;

	env = env_to_array(exec_data);
	if (execve(exec_data->cmds[i].path, exec_data->cmds[i].cmd,
			env) == -1)
	{
		free_array(env);
		ft_fatal_error(exec_data, "minishell", 127, &free_exec);
	}
}
