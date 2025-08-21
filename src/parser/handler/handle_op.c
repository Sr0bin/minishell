/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:53:29 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/21 18:08:59 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_op_extend(t_parser *p)
{
	if (p->crnt_pos != p->input && p->crnt_pos[0] != p->crnt_pos[-1])
	{
		token_generate(p, TOKEN_OPERATOR);
		p->start_pos--;
	}
	else
		p->crnt_pos++;
}

void	handle_op_other(t_parser *p)
{
	p->state = STATE_NORMAL;
	token_generate(p, TOKEN_OPERATOR);
	if (char_type(p->crnt_pos[-1]) != CHAR_OPERATOR && p->crnt_pos[-1] != '\0')
		p->crnt_pos--;
	if (p->start_pos != p->input)
		p->start_pos--;
}
