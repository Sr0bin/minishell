/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:16:31 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/19 13:48:32 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/builtins.h""

int	is_sorted(t_env *env)
{
	t_var	*var;
	t_var	*var2;

	while (env && env->next)
	{
		var = (t_var *)env->content;
		var2 = (t_var *)env->next->content;
		if (ft_strncmp(var->key, var2->key, ft_strlen(var->key)))
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

void	export_without_args(t_env *env)
{
	t_var	*var;
	t_var	*var2;
	int		sort;

	sort = 0;
	while (!sort)
	{
		sort = 1;
		while (env && env->next)
		{
			var = (t_var *)env->content;
			var2 = (t_var *)env->next->content;
			if (ft_strncmp(var->key, var2->key, ft_strlen(var2->key)) > 0)
			{
				ft_swap(env, env->next);
				sort = 0;
			}
			env = env->next;
		}
	}
	print_export_list(env);
}

void	print_export_list(t_env *env)
{
	t_var	*var;

	while (env)
	{
		var = (t_var *)env->content;
		if (var->value)
			printf("declare -x %s=%s\n", var->key, var->value);
		else
			printf("declare -x %s\n", var->key);
		env = env->next;
	}
}
