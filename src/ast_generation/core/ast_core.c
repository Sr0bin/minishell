/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:53:12 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/04 21:56:00 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/enums.h"

void	*ast_destroy(t_ast **node)
{
	if (*node == NULL)
		return (NULL);
	if ((*node)->type == NODE_PIPE)
	{
		if ((*node)->s_pipe.left != NULL)
			ast_destroy(&(*node)->s_pipe.left);
		if ((*node)->s_pipe.right != NULL)
			ast_destroy(&(*node)->s_pipe.right);
	}
	free_node(node);
	return (NULL);
}

void	*free_ast_machine(t_ast_machine **machine)
{
	free(*machine);
	*machine = NULL;
	return (NULL);
}

t_ast_machine	*create_ast_machine(t_token_list *input_list)
{
	t_ast_machine	*ast_machine;

	ast_machine = ft_calloc(1, sizeof(t_ast_machine));
	if (ast_machine == NULL)
		return (ft_error("AST Machine failed", MALLOC_FAILED));
	ast_machine->crnt_tkn_lst = input_list;
	ast_machine->crnt_tkn = input_list->content;
	return (ast_machine);
}

t_ast	*generate_node(t_node_type type, t_cmd cmd)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (node == NULL)
		return (ft_error("Node creation failed", MALLOC_FAILED));
	node->type = type;
	if (node->type == NODE_COMMAND)
		node->cmd = cmd;
	return (node);
}

void	*free_node(t_ast **node)
{
	if ((*node)->type == NODE_COMMAND)
		free_parser_cmd((*node)->cmd);
	free(*node);
	*node = NULL;
	return (NULL);
}
