/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:10:20 by rorollin          #+#    #+#             */
/*   Updated: 2025/05/28 17:10:04 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "minishell.h"
#include "struct.h"

t_char_type	char_type(char c)
{
	if (c == '\0')
		return (CHAR_EOF);
	if (c == ' ' || c == '\t')
		return (CHAR_WHITESPACE);
	if (c == '\'' || c == '"')
		return (CHAR_QUOTE);
	if (c == '<' || c == '>' || c == '|' || c == '&' || c == ';')
		return (CHAR_OPERATOR);
	if (c == '\n')
		return (CHAR_NEWLINE);
	if (c == '\\')
		return (CHAR_ESCAPE);
	return (CHAR_OTHER);
}


void	handle_normal(char c, t_parser *p)
{
	t_char_type type;

	type = char_type(c);
	if (type == CHAR_WHITESPACE)
		handle_normal_whitespace(c, p);
	else if (type == CHAR_QUOTE)
		handle_normal_quote(c, p);
	else if (type == CHAR_OPERATOR)
		handle_normal_operator(c, p);
	else if (type == CHAR_NEWLINE)
		handle_normal_newline(c, p);
	else if (type == CHAR_ESCAPE)
		handle_normal_escape(c, p);
	else if (type == CHAR_EOF)
		handle_normal_eof(c, p);
	else if (type == CHAR_OTHER)
		handle_normal_other(c, p);
}
void	handle_squote(char c, t_parser *p)
{
	t_char_type type;

	type = char_type(c);
	if (c == '\'')
		handle_squote_end(c, p);
}

