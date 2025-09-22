/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:10:17 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 14:50:51 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "minishell.h"
#include "struct.h"

void	handle_normal_whitespace(t_parser *p)
{
	if (p->crnt_pos != p->input
		&& char_type((p->crnt_pos)[-1]) != CHAR_WHITESPACE
		&& char_type((p->crnt_pos)[-1]) != CHAR_DQUOTE
		&& char_type((p->crnt_pos)[-1]) != CHAR_SQUOTE
		&& char_type((p->crnt_pos)[-1]) != CHAR_OPERATOR)
		token_generate(p, TOKEN_WORD);
	else
	{
		p->crnt_pos++;
		p->start_pos++;
	}
}

void	handle_normal_quote(t_parser *p)
{
	if (*(p->crnt_pos) == '\'')
		p->state = STATE_SQUOTE;
	else
		p->state = STATE_DQUOTE;
	if (p->crnt_pos != p->input && safe_char_type(p, -1) != CHAR_WHITESPACE)
	{
		token_generate(p, TOKEN_WORD);
		p->crnt_token->to_join = 1;
		p->crnt_pos--;
		p->start_pos--;
	}
	p->start_pos = p->crnt_pos;
	if (*(p->crnt_pos) != '\0')
		p->crnt_pos++;
}

void	handle_normal_operator(t_parser *p)
{
	p->state = STATE_OP;
	if (p->input != p->crnt_pos && safe_char_type(p, -1) != CHAR_WHITESPACE)
	{
		token_generate(p, TOKEN_WORD);
		p->crnt_pos--;
		p->start_pos--;
	}
	p->crnt_pos++;
}

void	handle_normal_other(t_parser *p)
{
	p->crnt_pos++;
}

void	handle_normal_escape(t_parser *p)
{
	remove_char(p->crnt_pos);
	p->crnt_pos++;
}
