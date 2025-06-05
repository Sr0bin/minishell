/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:09:13 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/04 15:14:16 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_sorted(t_list *env)
{
	t_var *var;
	t_var *var2;

	while (env && env->next)
	{
		var = (t_var *)env->content;
		var2 = (t_var*)env->next->content;
		if (ft_strncmp(var->key, var2->key, ft_strlen(var->key)))
			return (0);
		env = env->next;
	}
	return (1);
}

void	ft_swap(t_list *a, t_list *b)
{
	void *tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

void	export_without_args(t_list *env)
{
	t_list 	*tmp;
	t_var	*var;
	t_var	*var2;
	int		sort;
	
	sort = 0;
	while (!sort)
	{
		sort = 1;
		tmp = env;
		while (env && env->next)
		{
			var = (t_var *)env->content;
			var2 = (t_var *)env->next->content;
			if (ft_strncmp(env, env->next, ft_strlen(env)))
			{	
				ft_swap(env, env->next);
				sort = 0;
			}	
			env = env->next;
		}
	}
}

void	print_export_list(t_list *env)
{
	t_var	*var;

	while (env)
	{
		var = (t_var *)env->content;
		if (var->value)
			printf("declare -x %s=%s\n", var->key, var->value);
		else
			printf("declare -x %s\n", var->key);
	}
}

void	export_with_args(t_list *env, char **args)
{
	
}

void	ft_export(t_list *env, char **args)
{
	if (args == 0)
		export_without_args(env);
	else
		export_with_args(env, args);
}