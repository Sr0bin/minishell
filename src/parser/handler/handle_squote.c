/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_squote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:44:40 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/04 02:20:47 by rorollin         ###   ########.fr       */
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
	char	*join;

	
	p->crnt_pos++;
	join = join_check_quote(p);
	if (char_type(*p->crnt_pos) != CHAR_SQUOTE)
		p->state = STATE_NORMAL;
	token_generate(p, TOKEN_WORD);
	if (join != NULL)
		p->crnt_token->to_join = 1;
	if (char_type(p->crnt_pos[-1]) != CHAR_SQUOTE && p->crnt_pos[-1] != '\0')
		p->crnt_pos--;
	if (p->start_pos != p->input)
		p->start_pos--;
}

void	handle_squote_other(t_parser *p)
{
	p->crnt_pos++;
}
