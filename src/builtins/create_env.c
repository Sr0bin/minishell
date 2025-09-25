/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 09:33:49 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/25 20:57:14 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "libft.h"
#include "struct.h"

int	create_var_with_value(t_var *var, char *env, char *equal_sign)
{
	var->key = ft_substr(env, 0, (ft_strlen(env) - ft_strlen(equal_sign)));
	if (!var->key)
	{
		free(var);
		ft_error("minishell: ft_substr failed\n", 1);
		return (-1);
	}
	var->value = ft_strdup(equal_sign + 1);
	if (!var->value)
	{
		free_var(var);
		ft_error("minishell: ft_strdup failed\n", 1);
		return (-1);
	}
	return (0);
}

t_var	*create_var(char *env)
{
	t_var	*var;
	char	*equal_sign;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	equal_sign = ft_strchr(env, '=');
	if (equal_sign)
{
		if (create_var_with_value(var, env, equal_sign) == -1)
			return (NULL);
	}
	else
	{
		var->key = ft_strdup(env);
		if (!var->key)
		{
			free_var(var);
			ft_error("minishell: ft_strdup failed\n", 1);
			return (NULL);
		}
		var->value = NULL;
	}
	return (var);
}

static t_env	*envp_empty(void)
{
	t_env	*empty_env;
	t_var	*empty_var;
	char	*empty_key;
	// char	*empty_value;

	empty_key = ft_strdup("");
	if (empty_key == NULL)
		return (NULL);
	empty_var = create_var(empty_key);
	if (empty_var == NULL)
	{
		free(empty_key);
		return (NULL);
	}
	empty_env = ft_lstnew(empty_var);
	if (empty_env == NULL)
	{
		free(empty_var);
		free(empty_key);
		return (NULL);
	}
	return (empty_env);
}

t_list	*envp_to_list(char **envp)
{
	t_list	*list;
	t_list	*node;
	t_var	*var;
	int		i;

	list = NULL;
	i = 0;
	if (envp == NULL || *envp == NULL)
		return (envp_empty());
	while (envp[i])
	{
		var = create_var(envp[i]);
		if (!var)
			return (NULL);
		node = ft_lstnew(var);
		if (!node)
		{
			free_var(var);
			return (NULL);
		}
		ft_lstadd_back(&list, node);
		i++;
	}
	return (list);
}
