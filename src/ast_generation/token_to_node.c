/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:54:22 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/10 19:00:27 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*p(void *p)
{
	(void) p;
	return (NULL);
}

void	*free_token_only_list(t_token_list **t_list)
{
	ft_lstclear(t_list, (void (*)) p);
	return (NULL);
}

int	token_type_redir(t_token *token)
{
	if (token->type == TOKEN_PIPE)
		return (TOKEN_PIPE);
	if (token->type == TOKEN_REDIR_IN)
		return (TOKEN_REDIR_IN);
	if (token->type == TOKEN_REDIR_OUT)
		return (TOKEN_REDIR_OUT);
	if (token->type == TOKEN_REDIR_APPEND)
		return (TOKEN_REDIR_APPEND);
	if (token->type == TOKEN_HEREDOC)
		return (TOKEN_HEREDOC);
	return (0);
}
t_node_type	token_to_node_type(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return (NODE_PIPE);
	if (type == TOKEN_REDIR_IN)
		return (NODE_REDIR_IN);
	if (type == TOKEN_REDIR_OUT)
		return (NODE_REDIR_OUT);
	if (type == TOKEN_REDIR_APPEND)
		return (NODE_REDIR_APPEND);
	return (0);
}

t_token_list	*pipe_find_first(t_token_list *list)
{
	while (list != NULL && token_type_redir((t_token *) list->content) != TOKEN_PIPE)
		list = list->next;
	return (list);
}

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
