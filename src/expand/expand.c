/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:02:54 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 12:36:59 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*var_search(t_env *env, char *key)
{
	t_env		*crnt_var;
	size_t	len;

	crnt_var = env;
	while (crnt_var != NULL)
	{
		len = ft_strlen(((t_var *)(crnt_var->content))->key); 
		if (ft_strncmp(((t_var *)(crnt_var->content))->key, key, (size_t) len)
			== 0)
			return (crnt_var->content);
		crnt_var = crnt_var->next;
	}
	return (NULL);
}
