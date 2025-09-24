/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:23:50 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/24 15:53:05 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/token.h"
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

t_token	*token_clean_quote(t_token *tkn)
{
	size_t	len;

	len = ft_strlen(tkn->content);
	if (len == 1)
		return (tkn);
	if (tkn->content[0] == '\'' && tkn->content[len - 1] == '\'')
	{
		remove_char(tkn->content);
		tkn->content[len - 2] = '\0';
	}
	if (tkn->content[0] == '"' && tkn->content[len - 1] == '"')
	{
		remove_char(tkn->content);
		tkn->content[len - 2] = '\0';
	}
	return (tkn);
}

t_token_list	*generate_token_list(t_parser *parser)
{
	t_token_list	*final_list;
	t_token_list	*lst_temp;
	t_token			*tkn_temp;

	tkn_temp = NULL;
	final_list = NULL;
	while (parser_stop(parser))
	{
		tkn_temp = update_parser_token(parser);
		if (tkn_temp == NULL)
			return (token_list_destroy(&final_list));
		lst_temp = ft_lstnew(tkn_temp);
		if (lst_temp == NULL)
		{
			token_destroy(tkn_temp);
			return (token_list_destroy(&final_list));
		}
		ft_lstadd_back(&final_list, lst_temp);
		parser->crnt_token = NULL;
	}
	return (final_list);
}
