/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:25:17 by rorollin          #+#    #+#             */
/*   Updated: 2025/07/30 19:54:33 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"

t_ast_machine	*advance_token(t_ast_machine *mchn)
{
	if (mchn->crnt_tkn_lst->next != NULL)
	{
		mchn->crnt_tkn_lst = mchn->crnt_tkn_lst->next;
		mchn->crnt_tkn = mchn->crnt_tkn_lst->content;
		return (mchn);
	}
	return (NULL);
}

/*static t_token_list	*crnt_tkn_list(t_ast_machine *mchn)*/
/*{*/
/*	return (mchn->crnt_tkn_list);*/
/*}*/

t_ast	*generate_simple_command(t_ast_machine *mchn)
{
	t_ast	*node;

	node = generate_node(NODE_COMMAND, NULL);
	if (node == NULL)
		return (NULL);
	node->left = generate_node(NODE_COMMAND, mchn->crnt_tkn);
	if (node->left == NULL)
	{
		free_node(&node);
		return (NULL);
	}
	if (advance_token(mchn) != NULL)
	{
		if (token_to_node_type(mchn->crnt_tkn->type) == 0)
		{
			node->right = generate_node(NODE_COMMAND, mchn->crnt_tkn);
			if (node->right == NULL)
			{
				free_node(&(node->left));
				free_node(&node);
				return (NULL);
			}
		}
	}
	return (node);
}

t_ast	*generate_redir_node(t_ast_machine *mchn)
{
	t_token_list			*token_redir;
	t_ast		*node;

	token_redir = find_first_redir(mchn->crnt_tkn_lst);
	if (token_redir == NULL)
		return (generate_simple_command(mchn));
	node = generate_node(token_to_node_type(((t_token *)(token_redir->content))->type), token_redir->content);
	node->left = generate_simple_command(mchn);
	if (advance_token(mchn) == NULL)
		return (node);
	if (token_to_node_type(mchn->crnt_tkn->type) != 0)
	{
		if (advance_token(mchn) == NULL)
			return (node);

	}
	node->right = generate_simple_command(mchn);
	return (node);
}

t_ast	*generate_full_ast(t_token_list **list)
{
	t_ast *node;
	t_ast_machine	*mchn;

	mchn = create_ast_machine(*list);
	if (mchn == NULL)
		return (NULL);
	node = generate_redir_node(mchn);
	print_ast(node);
	/*free_token_only_list(list);*/
	return (node);
}
