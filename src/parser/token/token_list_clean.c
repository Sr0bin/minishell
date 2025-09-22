/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:22:58 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 10:59:33 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/enums.h"
#include "parsing/handler.h"
#include "parsing/token.h"

static t_token_list	*token_list_empty(t_token *crnt_tkn, t_token_list **lst_del)
{
	char	*cursor;

	cursor = crnt_tkn->content;
	while (char_type(*cursor) == CHAR_WHITESPACE && *cursor != '\0')
		cursor++;
	if (*cursor == '\0')
	{
		ft_lstpop(lst_del, (void *) token_destroy);
		return (*lst_del);
	}
	if (ft_strcmp(crnt_tkn->content, "") == 0)
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
	void	*ret;

	tkn = lst_to_tkn(tkn_lst);
	tkn_next = lst_to_tkn(tkn_lst->next);
	assign_token_type(tkn);
	ret = token_expand(tkn);
	if (ret == NULL)
		return (NULL);
	token_clean_quote(tkn);
	if (tkn_next != NULL && tkn->to_join == 1)
	{
		ret = token_join(tkn_lst, tkn_lst->next);
		if (tkn->content == NULL || ret == NULL)
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
	void			*ret;

	if (*list == NULL)
		return (*list);
	iter_prev = *list;
	iter = iter_prev;
	if (iter_prev->next != NULL)
	{
		ret = token_clean(iter);
		if (ret == NULL)
			return (token_list_destroy(list));
		iter = iter_prev->next;
	}
	while (iter != NULL)
	{
		crnt_token = iter->content;
		if (token_list_empty(crnt_token, &iter_prev))
			iter = iter_prev->next;
		else
		{
			ret = token_clean(iter);
			if (ret == iter->next)
				continue ;
			if (ret == NULL)
				return (token_list_destroy(list));
			if (iter_prev->next == NULL)
				break ;
			iter_prev = iter;
			iter = iter->next;
		}
	}
	return (*list);
}
