/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:22:58 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/08 18:51:03 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/token.h"

static t_token_list	*token_list_empty(t_token *crnt_token, t_token_list **lst_del)
{
	if (ft_strcmp(crnt_token->content, "") == 0)
	{
		ft_lstpop(lst_del, (void *) token_destroy);
		return (*lst_del);
	}
	return (NULL);
}

//TODO: remove only whitespace token
static t_token_list	*token_clean(t_token_list *tkn_lst)
{
	t_token	*tkn;
	t_token	*tkn_next;
	tkn = lst_to_tkn(tkn_lst);
	tkn_next = lst_to_tkn(tkn_lst->next);
	assign_token_type(tkn);
	//TODO: Error
	token_expand(tkn);
	token_clean_quote(tkn);
	if (tkn_next != NULL && tkn->to_join == 1)
	{
		//TODO: error
		token_join(tkn_lst, tkn_lst->next);
		if (tkn->content == NULL)
			return (NULL);
		return (tkn_lst->next);
	}
	return (tkn_lst);
}

t_token_list	*token_list_clean(t_token_list **list)
{
	t_token_list	*iter_prev;
	t_token_list	*iter;
	t_token			*crnt_token;

	if (*list == NULL)
		return (*list);
	iter_prev = *list;
	iter = iter_prev;
	if (iter_prev->next != NULL)
	{
		token_clean(iter);
		//TODO: error
		iter = iter_prev->next;
	}
	else
		iter = iter_prev;
	while (iter != NULL)
	{
		crnt_token = iter->content;
		if (token_list_empty(crnt_token, &iter_prev))
			iter = iter_prev->next;
		else
		{
			if (token_clean(iter) == iter->next)
				continue ;
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
