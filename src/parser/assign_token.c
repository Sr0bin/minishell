/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:23:50 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/08 16:32:15 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static t_token	*assign_token_operator(t_token *token)
{
	if (token->type == TOKEN_EOF)
		token->type = TOKEN_WORD;
	if (ft_strcmp(token->content, "|") == 0)
		token->type = TOKEN_PIPE;
	if (ft_strcmp(token->content, "<") == 0)
		token->type = TOKEN_REDIR_IN;
	if (ft_strcmp(token->content, ">") == 0)
		token->type = TOKEN_REDIR_OUT;
	if (ft_strcmp(token->content, ">>") == 0)
		token->type = TOKEN_REDIR_APPEND;
	if (ft_strcmp(token->content, "<<") == 0)
		token->type = TOKEN_HEREDOC;
	return (token);
}

t_token	*assign_token_type(t_token *token)
{
	assign_token_operator(token);
	return (token);
}
