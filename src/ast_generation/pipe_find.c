/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:04:29 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/26 16:44:49 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_count(t_token_list	*tkn_lst, t_token_list *last)
{
	int	count;

	count = 0;
	while (tkn_lst != NULL && (last == NULL || tkn_lst != last))
	{
		if (lst_to_tkn(tkn_lst)->type == TOKEN_PIPE)
			count++;
		tkn_lst = tkn_lst->next;
	}
	return (count);
}

t_token_list	*pipe_find_first(t_token_list *list)
{
	while (list != NULL && token_type_redir((t_token *) list->content) != TOKEN_PIPE)
		list = list->next;
	return (list);
}

t_token_list	*pipe_find_n(t_token_list *list, int count)
{
	t_token_list	*crnt_pipe;
	int				counter;

	counter = 0;
	crnt_pipe = list;
	if (count == 0)
		return (NULL);
	while (list != NULL && counter < count)
	{
		if (lst_to_tkn(list)->type == TOKEN_PIPE)
		{
			crnt_pipe = list;
			counter++;
		}
		list = list->next;
	}
	return (crnt_pipe);
}

t_token_list	*pipe_find_last(t_token_list *list)
{
	t_token_list	*crnt_pipe;

	crnt_pipe = list;
	while (list != NULL)
	{
		if (lst_to_tkn(list)->type == TOKEN_PIPE)
			crnt_pipe = list;
		list = list->next;
	}
	return (crnt_pipe);
}

t_token_list	*redir_find_first(t_token_list *list)
{
	while (list != NULL && (token_type_redir((t_token *) list->content) == 0))
		list = list->next;
	if (list != NULL && token_type_redir((t_token *) list->content) == TOKEN_PIPE)
		return (NULL);
	return (list);
}
