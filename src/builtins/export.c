/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:09:13 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/06 16:14:02 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_sorted(t_env *env)
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

void	ft_swap(t_env *a, t_env *b)
{
	void *tmp;

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

int	check_export_var(char *args)
{
	int	i;

	i = 0;
	if (ft_isalpha(args[0]) == 0 && args[0] != '_')
	{
		perror("minishell: export:");
		return (1);
	}
	else
	{
		while(args[i])
		{
			if (ft_isalnum(args[i]) == 0 && args[i] != '_')
			{
				perror("minishell: export");
				return (1);
			}
			i++;
		}
	}
	return (0);
}

void	parse_args(char *arg, t_var *var)
{
	char	*equal;
	size_t	key_len;

	equal = ft_strchr(arg, '=');
	if (equal == NULL)
	{
		var->key = ft_strdup(arg);
		var->value = NULL;
	}
	else
	{
		key_len = equal - arg;
		var->key = ft_substr(arg, 0, key_len);
		var->value = ft_substr(arg, key_len + 1, ft_strlen(arg) - (key_len + 1));
	}
}

int	check_in_env(t_env *env, t_var *var)
{
	t_var	*var_env;

	while (env)
	{
		var_env = (t_var *)env->content;
		if (ft_strncmp(var_env->key, var->key, ft_strlen(var_env->key)) == 0)
		{
			if (var->value)
			{
				free(var_env->value);
				var_env->value = ft_strdup(var->value);
			}
			return (0);
		}
		env = env->next;
	}
	return (1);
}

void	export_with_args(t_env **env, char **args)
{
	int		i;
	t_var	*var;
	
	i = 0;
	while (args[i])
	{
		if (check_export_var(args[i]) == 0)
		{
			var = malloc(sizeof(t_var));
			if (!var)
				perror("minishell: malloc:");
			parse_args(args[i], var);
			if (!check_in_env(*env, var))
				ft_lstadd_back(env, ft_lstnew(var));
			else
				free(var);
		}
		i++;
	}
}

void	ft_export(t_env **env, char **args)
{
	if (!args || !args[0])
		export_without_args(*env);
	else
		export_with_args(env, args);
}