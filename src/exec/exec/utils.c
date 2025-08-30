/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:58:11 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/30 11:48:35 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"

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
