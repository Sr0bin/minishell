/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 07:53:11 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/02 17:56:22 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"

char	**env_to_array(t_exec_data *exec_data)
{
	char	**array;
	char	*str_tmp;
	int		i;
	t_var	*var;
	t_list	*tmp;

	tmp = exec_data->envp;
	array = malloc(sizeof(char *) * ((unsigned long)ft_lstsize(tmp) + 1));
	if (!array)
		ft_error("minishell: malloc failed", 1);
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
