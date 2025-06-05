/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:10:20 by rorollin          #+#    #+#             */
/*   Updated: 2025/06/05 18:26:38 by rorollin         ###   ########.fr       */
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
	if (c == '\'')
		return (CHAR_SQUOTE);
	if (c == '"')
		return (CHAR_DQUOTE);
	if (c == '<' || c == '>' || c == '|' || c == '&' || c == ';')
		return (CHAR_OPERATOR);
	if (c == '\n')
		return (CHAR_NEWLINE);
	if (c == '\\')
		return (CHAR_ESCAPE);
	return (CHAR_OTHER);
}

void	handle_normal(t_parser *p)
{
	t_char_type type;

	type = char_type(*p->crnt_pos);
	if (type == CHAR_WHITESPACE)
		handle_normal_whitespace(p);
	else if (type == CHAR_SQUOTE || type == CHAR_DQUOTE)
		handle_normal_quote(p);
	else if (type == CHAR_OPERATOR)
		handle_normal_operator(p);
	else if (type == CHAR_NEWLINE)
		handle_normal_newline(p);
	else if (type == CHAR_ESCAPE)
		handle_normal_escape(p);
	else if (type == CHAR_EOF)
		handle_normal_eof(p);
	else if (type == CHAR_OTHER)
		handle_normal_other(p);
}

void	handle_squote(t_parser *p)
{
	t_char_type type;

	type = char_type(*p->crnt_pos);
	if (type == CHAR_SQUOTE)
		handle_squote_end(p);
	else
		handle_squote_other(p);
}

void	handle_dquote(t_parser *p)
{
	t_char_type type;

	type = char_type(*p->crnt_pos);
	if (type == CHAR_DQUOTE)
		handle_dquote_end(p);
	else if (type == CHAR_ESCAPE)
		handle_dquote_escape(p);
	else
		handle_dquote_other(p);
}
