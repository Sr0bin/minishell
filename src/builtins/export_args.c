/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:19:22 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/06 22:46:15 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

int	check_export_var(char *args)
{
	int	i;

	i = 0;
	if (!ft_isalpha(args[0]) && args[0] != '_')
	{
		ft_putendl_fd("minishell: export: not a valid identifier", 2);
		return (-1);
	}
	while (args[i] && args[i] != '=')
	{
		if (!ft_isalnum(args[i]) && args[i] != '_')
		{
			ft_putendl_fd("minishell: export: not a valid identifier", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	parse_args(char *arg, t_var *var)
{
	char	*equal;
	size_t	key_len;

	equal = ft_strchr(arg, '=');
	if (equal == NULL)
	{
		var->key = ft_strdup(arg);
		if (!var->key)
		{
			ft_error("minishell: ft_strdup failed", 1);
			return (-1);
		}
		var->value = NULL;
	}
	else
	{
		key_len = (size_t)(equal - arg);
		var->key = ft_substr(arg, 0, key_len);
		if (!var->key)	
		{
			ft_error("minishell: ft_substr failed", 1);
			return (-1);
		}
		var->value = ft_substr(arg, (unsigned int)(key_len + 1),
				ft_strlen(arg) - (key_len + 1));
		if (!var->value)
		{
			free(var->key);
			ft_error("minishell: ft_substr failed", 1);
			return (-1);
		}
	}
	return (0);
}

int	check_in_env(t_env *env, t_var *var)
{
	t_var	*var_env;

	while (env)
	{
		var_env = (t_var *)env->content;
		if (ft_strcmp(var_env->key, var->key) == 0)
		{
			if (var->value)
			{
				free(var_env->value);
				var_env->value = ft_strdup(var->value);
				if (!var_env->value)
				{
					ft_error("minishell: ft_strdup failed", 1);
					return (-1);
				}
			}
			return (1);
		}
		env = env->next;
	}
	return (0);
}
