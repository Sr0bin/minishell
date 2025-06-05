/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:10:17 by rorollin          #+#    #+#             */
/*   Updated: 2025/06/05 16:07:20 by rorollin         ###   ########.fr       */
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
	generate_token(p, TOKEN_WORD);
}

void	handle_normal_operator(t_parser *p)
{
	generate_token(p, TOKEN_WORD);
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
}
