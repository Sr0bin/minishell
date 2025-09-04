/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:02:54 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/04 02:06:30 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*var_search(t_env *env, const char *key)
{
	t_env	*crnt_var;
	ptrdiff_t	len;
	

	crnt_var = env;
	len = var_expand_end(key) - key;
	while (crnt_var != NULL && ft_strncmp(((t_var *) (crnt_var->content))->key, key, (size_t) len) == 0)
	{
		if (ft_strncmp(((t_var *) (crnt_var->content))->key, key, (size_t) len) == 0)
			return (crnt_var->content);
		crnt_var = crnt_var->next;
	}
	return (NULL);
}
