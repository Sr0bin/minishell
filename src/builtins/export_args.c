/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:19:22 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/17 16:29:12 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
		while (args[i])
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
		var->value = ft_substr(arg, key_len + 1,
				ft_strlen(arg) - (key_len + 1));
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
			{
				free(var->key);
				free(var);
			}
		}
		i++;
	}
}
