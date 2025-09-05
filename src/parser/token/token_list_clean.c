/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:22:58 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/04 22:57:44 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/token.h"

//TODO: remove only whitespace token
t_token_list	*token_list_clean(t_token_list **list)
{
	t_token_list	*iter_prev;
	t_token_list	*iter;
	t_token			*crnt_token;

	if (*list == NULL)
		return (*list);
	iter_prev = *list;
	if (iter_prev->next != NULL)
	{
		assign_token_type((*list)->content);
		iter = iter_prev;
		crnt_token = iter->content;
		token_expand(crnt_token);
		token_clean_quote(crnt_token);
		if (crnt_token->to_join == 1)
			token_join(iter, iter->next);
		iter = iter_prev->next;
	}
	else
		iter = iter_prev;
	while (iter != NULL)
	{
		crnt_token = iter->content;
		if (ft_strcmp(crnt_token->content, "") == 0)
		{
			ft_lstpop(&iter_prev, (void *) token_destroy);
			iter = iter_prev->next;
		}
		else
		{
			assign_token_type(crnt_token);
			token_expand(crnt_token);
			token_clean_quote(crnt_token);
			if (crnt_token->to_join == 1)
			{
				token_join(iter, iter->next);
				continue ;
			}
			if (iter_prev->next == NULL)
				break;
			iter_prev = iter;
			iter = iter->next;
		}
	}
	return (*list);
}

void	*token_ptr_destroy(t_token **token)
{
	if (*token != NULL)
		free((*token)->content);
	free(*token);
	*token = NULL;
	return (NULL);
}
void	*token_destroy(t_token *token)
{
	if (token != NULL)
		free(token->content);
	free(token);
	return (NULL);
}

void	*token_list_destroy(t_token_list **tkn_lst)
{
	ft_lstclear(tkn_lst, (void (*)) token_destroy);
	return (NULL);
}
