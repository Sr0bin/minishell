/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:49:00 by rorollin          #+#    #+#             */
/*   Updated: 2025/06/05 16:06:09 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dquote_end(t_parser *p)
{
	p->state = STATE_NORMAL;
	generate_token(p, TOKEN_WORD);
}

// This is POSIX 2.2.3
void	handle_dquote_escape(t_parser *p)
{
	if (*(p->crnt_pos) == '$' || *(p->crnt_pos) == '`' || *(p->crnt_pos) == '"'\
		|| *(p->crnt_pos) == '\\' || *(p->crnt_pos) == '\n')
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
