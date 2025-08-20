/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_normal_end.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:55:47 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/20 17:56:15 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_normal_newline(t_parser *p)
{
	token_generate(p, TOKEN_WORD);
}

void	handle_normal_eof(t_parser *p)
{
	token_generate(p, TOKEN_EOF);
}
