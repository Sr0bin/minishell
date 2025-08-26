/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 07:53:11 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/26 08:17:49 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/exec/multipipes.h"

char	**t_env_to_array(t_exec_data *exec_data)
{
	char	**array;
	char	*str_tmp;
	int		i;
	t_var	*var;
	t_list	*tmp;

	tmp = exec_data->envp;
	array = malloc(sizeof(char *) * ((unsigned long)ft_lstsize(tmp) + 1));
	if (!array)
		ft_error (exec_data, "minishell: malloc failed", 1);
	i = 0;
	while (tmp)
	{
		var = (t_var *)tmp->content;
		str_tmp = ft_strjoin(var->key, "=");
		if (var->value)
			array[i] = ft_strjoin(str_tmp, var->value);
		else
			array[i] = ft_strdup(str_tmp);
		free(str_tmp);
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}
