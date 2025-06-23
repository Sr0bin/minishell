/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:22:49 by rorollin          #+#    #+#             */
/*   Updated: 2025/06/23 17:18:58 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	print_token(t_token token)
{
	printf("\n Token content : \"%s\" \n token Type : %i\n", token.content, token.type);
	
}

void	print_token_list(t_token_list *list)
{
	t_token_list *temp;

	temp = list;
	while (temp != NULL && temp->content != NULL)
	{
		print_token(*(t_token *) temp->content);
		temp = temp->next;
	}

}

static const char	*get_state_name(t_ps_state state)
{
	if (state == STATE_NORMAL)
		return ("STATE_NORMAL");
	if (state == STATE_SQUOTE)
		return ("STATE_SQUOTE");
	if (state == STATE_DQUOTE)
		return ("STATE_DQUOTE");
	return ("UNKNOWN_STATE");
}

void	print_parser_state(t_parser *parser)
{
	printf("=== Parser State ===\n");
	printf("State: %s\n", get_state_name(parser->state));
	printf("Input: |%s|\n", parser->input);
	printf("Current Position: |%s|\n", parser->crnt_pos);
	printf("Start Position: |%s|\n", parser->start_pos);
	if (parser->crnt_token)
	{
		printf("Current Token:\n");
		print_token(*(parser->crnt_token));
	}
	else
	{
		printf("Current Token: NULL\n");
	}
	printf("====================\n");
}
