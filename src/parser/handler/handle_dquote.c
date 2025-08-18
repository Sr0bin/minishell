/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:49:00 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/18 16:03:53 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dquote_end(t_parser *p)
{
	p->state = STATE_NORMAL;
	p->crnt_pos++;
	token_generate(p, TOKEN_WORD);
	if (char_type(p->crnt_pos[-1]) != CHAR_DQUOTE && p->crnt_pos[-1] != '\0')
		p->crnt_pos--;
	if (p->start_pos != p->input)
		p->start_pos--;
}

void	handle_dquote_eof(t_parser *p)
{
	quote_eof(p);
}

// This is POSIX 2.2.3
void	handle_dquote_escape(t_parser *p)
{
	if (*(p->crnt_pos + 1) == '$' || *(p->crnt_pos + 1) == '`'\
		|| *(p->crnt_pos + 1) == '"'\
		|| *(p->crnt_pos + 1) == '\\' || *(p->crnt_pos + 1) == '\n')
	{
		remove_char(p->crnt_pos);
		p->crnt_pos++;
		return ;
	}
	p->crnt_pos++;
}

void	handle_dquote_other(t_parser *p)
{
	p->crnt_pos++;
}
