/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:40:49 by rorollin          #+#    #+#             */
/*   Updated: 2025/07/03 16:21:29 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "list.h"
#include "minishell.h"
#include "struct.h"
#include "token.h"
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
	return (parser);
}

void	advance_parser(t_parser	*parser)
{
	print_parser_state(parser);
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
	while (parser->crnt_token == NULL)
		advance_parser(parser);
	return (parser->crnt_token);
}

int	parser_stop(t_parser *p)
{
	if (*(p->crnt_pos) == '\0')
	{
		if (p->state == STATE_DQUOTE || p->state == STATE_SQUOTE || p->state == STATE_OP)	
			return (1);
		return (0);
	}
	return (1);
}

t_token_list	*generate_token_list(t_parser *parser)
{
	t_token_list	*final_list;
	t_token_list	*lst_temp;
	t_token	*tkn_temp;

	tkn_temp = NULL;
	final_list = NULL;
	while (parser_stop(parser))
	{
		tkn_temp = update_parser_token(parser);
		if (tkn_temp == NULL)	// if memory error in token creation
			return (free_token_list(&final_list));
		lst_temp = ft_lstnew(tkn_temp);
		if (lst_temp == NULL)
			return (free_token_list(&final_list));
		ft_lstadd_back(&final_list, lst_temp);
		parser->crnt_token = NULL;
	}
	return (final_list);
}

t_token	*generate_token(t_parser *parser, t_token_type type)
{
	t_token	*token;
	char	*token_content;
	ptrdiff_t	len;

	len = parser->crnt_pos - parser->start_pos;
	token_content = malloc((unsigned) (len + 1) * sizeof(char));
	if (token_content == NULL)
		return (NULL);
	ft_strlcpy(token_content, parser->start_pos, (unsigned) len + 1);
	token = create_token(token_content, type);
	if (token == NULL)
	{
		free(token_content);
		return (NULL);
	}
	parser->crnt_token = token;
	if (*parser->crnt_pos != '\0')
	{
		parser->crnt_pos++;
		parser->start_pos = parser->crnt_pos;
	}
	return (token);
}

t_token_list	*shell_tokenizer(char *input)
{
	t_parser		*parser;
	t_token_list	*final_list;
	/*t_token			*temp;*/

	parser = parser_init(input);
	if (parser == NULL)
		return (NULL);
	final_list = generate_token_list(parser);
	free(parser);
	if (final_list == NULL)
		return (NULL);
	return (final_list);
}
