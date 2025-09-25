/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:45:27 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/25 22:13:27 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

int	create_new_var(t_exec_data *exec_data, const char *key, const char *value)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (-1);
	var->key = ft_strdup(key);
	var->value = ft_strdup(value);
	if (!var->key || !var->value)
	{
		free(var->key);
		free(var->value);
		free(var);
		ft_error("minishell: ft_strdup failed\n", 1);
		return (-1);
	}
	ft_lstadd_back(&exec_data->envp, ft_lstnew(var));
	return (0);
}
