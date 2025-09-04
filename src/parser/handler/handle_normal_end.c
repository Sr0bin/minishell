/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_normal_end.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:55:47 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/04 21:46:49 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_normal_newline(t_parser *p)
{
	token_generate(p, TOKEN_WORD);
}

void	handle_normal_eof(t_parser *p)
{
	char	*join;

	join = join_check_normal(p);
	token_generate(p, TOKEN_WORD);
	if (p->crnt_token != NULL && join != NULL)
		p->crnt_token->to_join = 1;
}
