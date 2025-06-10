xc99/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:28:51 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/03 15:41:33 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_var(t_list *env, char *key, char *value)
{
	while(env && env->next)
	{
		if (ft_strncmp(env->content.key, key, ft_strlen(key)) == 0)
		{
			env->content.value = ft_strdup(value);
			return (0);
		}
		env = env->next;
	}
	return (1);
}

void	ft_export(t_list *env, char *key, char *value)
{
	if (check_var(env, key, value) == 0)
		return ;
	else
	{
		ft_lstadd_back(env, )
	}
}