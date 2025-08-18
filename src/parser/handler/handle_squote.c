/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_squote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:44:40 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/18 16:04:09 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	quote_eof(t_parser *p)
{
	p->crnt_token = token_create(ft_strdup("ERROR"), TOKEN_EOF);
	p->state = STATE_NORMAL;
}

void	handle_squote_eof(t_parser *p)
{
	quote_eof(p);
}

void	handle_squote_end(t_parser *p)
{
	p->state = STATE_NORMAL;
	p->crnt_pos++;
	token_generate(p, TOKEN_WORD);
	if (char_type(p->crnt_pos[-1]) != CHAR_SQUOTE && p->crnt_pos[-1] != '\0')
		p->crnt_pos--;
	if (p->start_pos != p->input)
		p->start_pos--;
}

void	handle_squote_other(t_parser *p)
{
	p->crnt_pos++;
}
