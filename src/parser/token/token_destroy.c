/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:53:56 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 10:54:29 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*token_ptr_destroy(t_token **token)
{
	if (*token != NULL)
		free((*token)->content);
	free(*token);
	*token = NULL;
	return (NULL);
}
void	*token_destroy(t_token *token)
{
	if (token != NULL)
		free(token->content);
	free(token);
	return (NULL);
}

void	*token_list_destroy(t_token_list **tkn_lst)
{
	ft_lstclear(tkn_lst, (void (*)) token_destroy);
	return (NULL);
}
