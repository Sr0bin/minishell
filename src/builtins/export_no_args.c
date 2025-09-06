/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:16:31 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/05 20:20:51 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

int	is_sorted(t_env *env)
{
	t_var	*var;
	t_var	*var2;

	while (env && env->next)
	{
		var = (t_var *)env->content;
		var2 = (t_var *)env->next->content;
		if (ft_strcmp(var->key, var2->key))
			return (0);
		env = env->next;
	}
	return (1);
}

void	ft_swap(t_env *a, t_env *b)
{
	void	*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

void	print_export_list(t_env *env)
{
	t_var	*var;

	while (env)
	{
		var = (t_var *)env->content;
		if (var->value && var->key[0] != '_')
			printf("export %s=\"%s\"\n", var->key, var->value);
		else if (var->key[0] != '_')
			printf("export %s\n", var->key);
		env = env->next;
	}
}
