/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:09:50 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/05 11:39:27 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_env(t_list *env)
{
	t_var *var;

	while (env)
	{	
		var = (t_var *)env->content;
		if (var->value)
			printf("%s=%s\n", var->key, var->value);
		env = env->next;
	}
}
