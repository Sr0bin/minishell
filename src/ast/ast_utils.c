/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:53:12 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/10 17:03:27 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/enums.h"

/*void	*free_ast(t_ast **node)*/
/*{*/
/*	if ((*node)->left != NULL)*/
/*		free_ast(&(*node)->left);*/
/*	if ((*node)->right != NULL)*/
/*		free_ast(&(*node)->right);*/
/*	clean_free_token(&((*node)->token));*/
/*	(*node)->token = NULL;*/
/*	free_node(node);*/
/*	return (NULL);*/
/*}*/

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
		return (NULL);
	ast_machine->crnt_tkn_lst = input_list;
	ast_machine->crnt_tkn = input_list->content;
	return (ast_machine);
}

t_ast	*generate_node(t_node_type type, t_cmd cmd)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (node == NULL)
		return (NULL);
	node->type = type;
	if (node->type == NODE_COMMAND)
		node->cmd = cmd;
	/*node->token = token;*/
	return (node);
}

void	*free_node(t_ast **node)
{
	free(*node);
	*node = NULL;
	return (NULL);
}
