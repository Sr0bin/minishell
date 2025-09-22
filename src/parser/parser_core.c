/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:40:49 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 10:29:31 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "list.h"
#include "minishell.h"
#include "struct.h"
#include <stddef.h>

t_parser	*parser_init(char *input)
{
	t_parser	*parser;

	parser = ft_calloc(1, sizeof(t_parser));
	parser->state = STATE_NORMAL;
	parser->input = input;
	parser->crnt_pos = input;
	parser->start_pos = input;
	parser->crnt_token = NULL;
	parser->token_list = NULL;
	parser->error_code = 0;
	return (parser);
}

void	advance_parser(t_parser	*parser)
{
	if (parser->state == STATE_NORMAL)
		handle_normal(parser);
	else if (parser->state == STATE_SQUOTE)
		handle_squote(parser);
	else if (parser->state == STATE_DQUOTE)
		handle_dquote(parser);
	else if (parser->state == STATE_OP)
		handle_op(parser);
}

void	*update_parser_token(t_parser *parser)
{
	while (parser->crnt_token == NULL && parser->error_code == 0)
		advance_parser(parser);
	return (parser->crnt_token);
}

int	parser_stop(t_parser *p)
{
	if (p->error_code != 0)
		return (0);
	if (*(p->crnt_pos) == '\0')
	{
		if (p->state == STATE_DQUOTE || p->state == STATE_SQUOTE || p->state == STATE_OP)
			return (1);
		return (0);
	}
	return (1);
}

t_token_list	*shell_tokenizer(char *input)
{
	t_parser		*parser;
	t_token_list	*final_list;

	parser = parser_init(input);
	if (parser == NULL)
		return (NULL);
	final_list = generate_token_list(parser);
	parser_handle_error(parser, &final_list);
	free(parser);
	return (final_list);
}
