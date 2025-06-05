/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:40:49 by rorollin          #+#    #+#             */
/*   Updated: 2025/06/05 16:16:55 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (parser->state == STATE_NORMAL)
		handle_normal(parser);
	else if (parser->state == STATE_SQUOTE)
		handle_squote(parser);
	else if (parser->state == STATE_DQUOTE)
		handle_dquote(parser);
}

void	*update_parser_token(t_parser *parser)
{
	parser->crnt_token = NULL;
	while (*(parser->crnt_pos) != '\0')
		advance_parser(parser);
	return (parser->crnt_token);
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
	parser->crnt_pos++;
	parser->start_pos = parser->crnt_pos;
	return (token);
}

t_token_list	*generate_token_list(t_parser *parser)
{
	t_token_list	*list;
	t_token_list	*temp;

	list = NULL;
	while (*(parser->crnt_pos) != '\0')
	{
		while (parser->crnt_token == NULL)
		{
			if (update_parser_token(parser) == NULL)	// if memory error in token creation
				return (free_token_list(&list));
		}
		temp = ft_lstnew(parser->crnt_token);
		if (temp == NULL)
			return (free_token_list(&list));
		ft_lstadd_back(&list, temp);
	}


	return (list);
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
