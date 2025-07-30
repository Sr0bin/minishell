/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:53:12 by rorollin          #+#    #+#             */
/*   Updated: 2025/07/30 19:40:47 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_ast(t_ast **node)
{
	if ((*node)->left != NULL)
		free_ast(&(*node)->left);
	if ((*node)->right != NULL)
		free_ast(&(*node)->right);
	free_token((*node)->token);
	free_node(node);
	return (NULL);
}

t_ast_machine	*create_ast_machine(t_token_list *input_list)
{
	t_ast_machine	*ast_machine;

	ast_machine = ft_calloc(1, sizeof(t_ast_machine));
	ast_machine->tkn_lst = input_list;
	ast_machine->crnt_tkn_lst = input_list;
	ast_machine->crnt_tkn = input_list->content;
	return (ast_machine);
}

t_ast	*generate_node(t_node_type type, t_token *token)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (node == NULL)
		return (NULL);
	node->type = type;
	node->token = token;
	return (node);
}

void	*free_node(t_ast **node)
{
	free(*node);
	*node = NULL;
	return (NULL);
}
