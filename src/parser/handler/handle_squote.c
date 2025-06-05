/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_squote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:44:40 by rorollin          #+#    #+#             */
/*   Updated: 2025/06/05 15:55:59 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	handle_squote_end(t_parser *p)
{
	p->state = STATE_NORMAL;
	generate_token(p, TOKEN_WORD);
	
}

void	handle_squote_other(t_parser *p)
{
	p->crnt_pos++;
}
