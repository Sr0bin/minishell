/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:22:58 by rorollin          #+#    #+#             */
/*   Updated: 2025/07/19 16:42:10 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list	*clean_token_list(t_token_list **list)
{
	t_token_list	*iter_prev;
	t_token_list	*iter;
	t_token			*crnt_token;

	if (*list == NULL)
		return (*list);
	iter_prev = *list;
	if (iter_prev->next != NULL)
		iter = iter_prev->next;
	else
		iter = iter_prev;
	while (iter != NULL)
	{
		crnt_token = iter->content;
		if (ft_strcmp(crnt_token->content, "") == 0)
			ft_lstpop(&iter_prev, (void *) free_token);
		else
			assign_token_type(crnt_token);
		iter_prev = iter_prev->next;
		if (iter_prev != NULL)
			iter = iter_prev->next;
		else
			iter = NULL;
	}
	return (*list);
}
