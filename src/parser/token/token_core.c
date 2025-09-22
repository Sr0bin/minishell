/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:53:27 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/19 18:57:59 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "minishell.h"

t_token	*token_create(char *text, t_token_type type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (new == NULL)
		return (NULL);
	*new = (const t_token){0};
	new->content = text;
	new->type = type;
	new->to_join = 0;
	return (new);
}

t_token	*token_generate(t_parser *p, t_token_type type)
{
	t_token		*token;
	char		*token_content;
	ptrdiff_t	len;

	len = p->crnt_pos - p->start_pos;
	token_content = malloc((unsigned)(len + 1) * sizeof(char));
	if (token_content == NULL)
		return (parser_update_error(p, MALLOC_FAIL));
	ft_strlcpy(token_content, p->start_pos, (unsigned) len + 1);
	token = token_create(token_content, type);
	if (token == NULL)
	{
		free(token_content);
		return (parser_update_error(p, MALLOC_FAIL));
	}
	p->crnt_token = token;
	if (*p->crnt_pos != '\0')
	{
		p->crnt_pos++;
		p->start_pos = p->crnt_pos;
	}
	return (token);
}

t_token_list	*token_list_create(t_token *first)
{
	t_token_list	*list;

	list = ft_lstnew((void *) first);
	return (list);
}

void	*token_list_add(t_token_list **list, t_token_list *token)
{
	ft_lstadd_back(list, token);
	return (token);
}

inline t_token	*lst_to_tkn(t_token_list *tkn_list)
{
	if (tkn_list == NULL)
		return (NULL);
	return ((t_token *)tkn_list->content);
}
