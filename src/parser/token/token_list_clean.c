/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:22:58 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/25 17:49:04 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "minishell.h"
#include "parsing/enums.h"
#include "parsing/handler.h"
#include "parsing/token.h"

static t_token_list	*token_list_empty(t_token *crnt_tkn, t_token_list **lst_del)
{
	if (ft_strcmp(crnt_tkn->content, "") == 0)
	{
		ft_lstpop(lst_del, (void *) token_destroy);
		return (*lst_del);
	}
	return (NULL);
}

static t_token	*token_expand_loop(t_token	*tkn)
{
	void	*ret;
	char	*crnt_pos;

	if (tkn->content[0] == '\'')
		return (tkn);
	crnt_pos = ft_strchr(tkn->content, '$');
	while (crnt_pos++ != NULL)
	{
		ret = token_expand(tkn);
		if (ret == NULL)
			return (NULL);
		crnt_pos = ft_strchr(tkn->content, '$');
	}
	return (tkn);
}

static t_token_list	*token_clean(t_token_list *tkn_lst)
{
	t_token	*tkn;
	t_token	*tkn_next;
	void	*ret;

	tkn = lst_to_tkn(tkn_lst);
	tkn_next = lst_to_tkn(tkn_lst->next);
	assign_token_type(tkn);
	token_expand_loop(tkn);
	token_clean_quote(tkn);
	if (tkn_next != NULL && tkn->to_join == 1)
	{
		ret = token_join(tkn_lst);
		if (tkn->content == NULL || ret == NULL)
			return (NULL);
		token_expand_loop(tkn);
		return (ret);
	}
	return (tkn_lst);
}

static t_token_list	**token_list_loop(t_token_list **tkn_lst,
									t_token_list *iter_prev)
{
	t_token_list	*iter;
	t_token			*crnt_token;
	void			*ret;

	iter = *tkn_lst;
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
				return (token_list_destroy(tkn_lst));
			if (iter_prev->next == NULL)
				break ;
			iter_prev = iter;
			iter = iter->next;
		}
	}
	return (tkn_lst);
}

t_token_list	*token_list_clean(t_token_list **tkn_lst)
{
	t_token_list	*iter_prev;
	t_token_list	*iter;
	void			*ret;

	if (*tkn_lst == NULL)
		return (*tkn_lst);
	iter_prev = *tkn_lst;
	iter = iter_prev;
	if (iter_prev->next != NULL)
	{
		ret = token_clean(iter);
		if (ret == NULL)
			return (token_list_destroy(tkn_lst));
		iter = iter_prev->next;
	}
	ret = token_list_loop(&iter, iter_prev);
	if (ret == NULL)
		return (NULL);
	return (*tkn_lst);
}
