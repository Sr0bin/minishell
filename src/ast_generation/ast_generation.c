/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:25:17 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 09:24:07 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

t_ast	*ast_create(t_token_list **list)
{
	t_ast	*node;

	if (*list == NULL)
		return (NULL);
	node = node_pipe_create(*list, pipe_find_last(*list)->next);
	if (node == NULL)
	{
		ast_destroy(&node);
		ft_error("Memory error in AST generation.\n", 127);
	}
	return (node);
}
