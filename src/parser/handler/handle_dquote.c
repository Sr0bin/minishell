/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:49:00 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/04 21:45:36 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dquote_end(t_parser *p)
{
	char	*join;

	p->crnt_pos++;
	join = join_check_quote(p);
	if (char_type(*p->crnt_pos) != CHAR_DQUOTE)
		p->state = STATE_NORMAL;
	token_generate(p, TOKEN_WORD);
	if (p->crnt_token != NULL && join != NULL)
		p->crnt_token->to_join = 1;
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
