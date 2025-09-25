/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:09:50 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/25 21:17:01 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

int	ft_env(t_env *env)
{
	t_var	*var;

	while (env)
	{
		var = (t_var *)env->content;
		if (var->key != NULL && *var->key == '\0')
		{
			env = env->next;
			continue ;
		}
		if (var && var->value)
			printf("%s=%s\n", var->key, var->value);
		env = env->next;
	}
	return (0);
}
