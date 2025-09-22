/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:50:23 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 14:51:08 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_check_normal(t_parser *p)
{
	if (char_type(p->crnt_pos[-1]) == CHAR_SQUOTE
		|| char_type(p->crnt_pos[-1]) == CHAR_DQUOTE)
		return (&p->start_pos[-1]);
	return (NULL);
}

char	*join_check_quote(t_parser *p)
{
	if (char_type(p->crnt_pos[0]) == CHAR_OTHER)
		return (p->crnt_pos);
	return (NULL);
}
