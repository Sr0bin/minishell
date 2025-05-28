/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:40:49 by rorollin          #+#    #+#             */
/*   Updated: 2025/05/28 14:10:33 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"

t_ps_state	parser_state(t_ps_state new_state, bool update)
{
	static t_ps_state	state = STATE_DEFAULT;

	if (update)
		state = new_state;
	return (state);
}

t_token_list	shell_parser(char *input)
{

}
