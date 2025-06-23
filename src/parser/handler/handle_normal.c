/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:10:17 by rorollin          #+#    #+#             */
/*   Updated: 2025/06/23 19:14:58 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "minishell.h"
#include "struct.h"

void	handle_normal_whitespace(t_parser *p)
{
	ptrdiff_t len;

	len = p->crnt_pos - p->start_pos;
	if (len == 0)
	{
		p->crnt_pos++;
		p->start_pos++;
		return ;
	}
	generate_token(p, TOKEN_WORD);
}

void	handle_normal_quote(t_parser *p)
{
	if (*(p->crnt_pos) == '\'')
		p->state = STATE_SQUOTE;
	else
		p->state = STATE_DQUOTE;
	if (p->crnt_pos == p->input || char_type(p->crnt_pos[-1]) != CHAR_WHITESPACE)
		generate_token(p, TOKEN_WORD);
	/*if (*(p->crnt_pos) != '\0')*/
	/*{*/
	/*	p->crnt_pos++;*/
	/*	p->start_pos++;*/
	/*}*/
}

void	handle_normal_operator(t_parser *p)
{
	p->crnt_pos++;
	/*generate_token(p, TOKEN_WORD);*/
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

void	handle_normal_newline(t_parser *p)
{
	generate_token(p, TOKEN_WORD);
}

void	handle_normal_eof(t_parser *p)
{
	generate_token(p, TOKEN_WORD);
	p->start_pos--;
	p->crnt_pos--;
}
