/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:58:11 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/03 13:44:01 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (!ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}

char	*get_env_value(t_exec_data *exec_data, char *key)
{
	t_var	*var;
	t_env	*current;

	current = exec_data->envp;
	while (current)
	{
		var = (t_var *)current->content;
		if (ft_strcmp(var->key, key) == 0)
			return (var->value);
		current = current->next;
	}
	return (NULL);
}
