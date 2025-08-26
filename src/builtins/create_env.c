/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 09:33:49 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/26 08:20:33 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include "libft.h"
#include "struct.h"

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
		var->key = ft_substr(env, 0, (ft_strlen(env) - ft_strlen(equal_sign)));
		var->value = ft_strdup(equal_sign + 1);
	}
	else
	{
		var->key = ft_strdup(env);
		var->value = NULL;
	}
	return (var);
}

t_list	*envp_to_list(char **envp)
{
	t_list	*list;
	t_list	*node;
	t_var	*var;
	int		i;

	list = NULL;
	i = 0;
	while (envp[i])
	{
		var = create_var(envp[i]);
		if (!var)
		{
			free(var);
			return (NULL);
		}
		node = ft_lstnew(var);
		if (!node)
		{
			free(var);
			return (NULL);
		}
		ft_lstadd_back(&list, node);
		i++;
	}
	return (list);
}
