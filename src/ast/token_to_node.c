/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:54:22 by rorollin          #+#    #+#             */
/*   Updated: 2025/07/19 17:55:53 by rorollin         ###   ########.fr       */
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
t_node_type token_to_node_type(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return (NODE_PIPE);
	if (type == TOKEN_REDIR_IN)
		return (NODE_REDIR_IN);
	if (type == TOKEN_REDIR_OUT)
		return (NODE_REDIR_OUT);
	if (type == TOKEN_REDIR_APPEND)
		return (NODE_REDIR_APPEND);
	return (NODE_ERROR);
}
t_token_list	*find_first_redir(t_token_list *list)
{
	while (list != NULL && token_type_redir((t_token *) list->content) == 0)
		list = list->next;
	return (list);
}

