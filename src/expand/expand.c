/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:02:54 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 17:39:58 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*var_search(char *key)
{
	t_env	*env;
	t_env	*crnt_var;
	size_t	len_var;
	size_t	len_key;

	env = context_read()->env;
	crnt_var = env;
	len_key = (size_t)(var_expand_end(key) - key);
	while (crnt_var != NULL)
	{
		len_var = ft_strlen(((t_var *)(crnt_var->content))->key);
		if (len_var != len_key)
			;
		else if (ft_strncmp(((t_var *)(crnt_var->content))->key, key, len_var)
			== 0)
			return (crnt_var->content);
		crnt_var = crnt_var->next;
	}
	return (NULL);
}
