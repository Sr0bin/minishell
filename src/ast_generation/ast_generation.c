/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:25:17 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/24 15:28:35 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	*ast_check_cmd(t_ast *node)
{
	if (node == NULL)
		return (NULL);
	if (node->type == NODE_COMMAND)
	{
		if (*node->cmd.args == NULL && node->cmd.redir == NULL)
			return (NULL);
	}
	if (node->type == NODE_PIPE)
	{
		if (ast_check_cmd(node->s_pipe.left) == NULL
			|| ast_check_cmd(node->s_pipe.right) == NULL)
			return (NULL);
	}
	return (node);
}

t_ast	*ast_create(t_token_list **list)
{
	t_ast	*node;

	if (*list == NULL)
		return (NULL);
	node = node_pipe_create(*list, pipe_find_last(*list)->next);
	if (node == NULL)
	{
		ast_destroy(&node);
		ft_error("Error in AST generation.\n", 127);
	}
	if (ast_check_cmd(node) == NULL)
	{
		ast_destroy(&node);
		ft_error("Syntax error : Empty pipeline\n", 127);
	}
	return (node);
}
