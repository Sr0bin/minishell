/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:02:54 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/08 18:31:51 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*var_search(t_env *env, char *key_to_search)
{
	t_env	*crnt_var;
	ptrdiff_t	len;
	
	crnt_var = env;
	len = var_expand_end(key_to_search) - key_to_search;
	while (crnt_var != NULL)
	{
		if (ft_strncmp(((t_var *) (crnt_var->content))->key, key_to_search, (size_t) len) == 0)
			return (crnt_var->content);
		crnt_var = crnt_var->next;
	}
	return (NULL);
}
