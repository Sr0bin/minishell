/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:53:27 by rorollin          #+#    #+#             */
/*   Updated: 2025/07/31 03:37:56 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "minishell.h"

t_token	*create_token(char *text, t_token_type type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (new == NULL)
		return (NULL);
	*new = (const t_token){0};
	new->content = text;
	new->type = type;
	return (new);
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

t_token_list	*create_token_list(t_token *first)
{
	t_token_list *list;

	list = ft_lstnew((void *) first);
	return (list);
}

void	*add_token(t_token_list **list, t_token_list *token)
{
	ft_lstadd_back(list, token);
	return (token);
}

void	*clean_free_token(t_token **token)
{
	if (*token != NULL)
		free((*token)->content);
	free(*token);
	*token = NULL;
	return (NULL);
}
void	*free_token(t_token *token)
{
	if (token != NULL)
		free(token->content);
	free(token);
	return (NULL);
}

void	*free_token_list(t_token_list **t_list)
{
	ft_lstclear(t_list, (void (*)) free_token);
	return (NULL);
}
