/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:25:17 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/04 20:02:45 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"

t_ast_machine	*advance_token(t_ast_machine *mchn)
{
	if (mchn->crnt_tkn_lst != NULL && mchn->crnt_tkn_lst->next != NULL)
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
	if (advance_token(mchn) != NULL && token_to_node_type(mchn->crnt_tkn->type) == 0)
	{
		node->right = generate_node(NODE_COMMAND, mchn->crnt_tkn);
		if (node->right == NULL)
		{
			free_node(&(node->left));
			free_node(&node);
			return (NULL);
		}
		while (advance_token(mchn) != NULL && token_to_node_type(mchn->crnt_tkn->type) == 0)
		{
			ft_strcat(&(node->right->token->content), mchn->crnt_tkn->content);
			free(mchn->crnt_tkn);
		}
	}
	advance_token(mchn);
	return (node);
}

t_ast	*generate_redir_node(t_ast_machine *mchn)
{
	t_ast	*node;

	mchn->crnt_redir_ptr = find_first_redir(mchn->crnt_redir_ptr);
	if (mchn->crnt_redir_ptr == NULL)
		return (generate_simple_command(mchn));
	node = generate_node(token_to_node_type(((t_token *)(mchn->crnt_redir_ptr->content))->type), mchn->crnt_redir_ptr->content);
	mchn->crnt_redir_ptr = mchn->crnt_redir_ptr->next;
	node->left = generate_redir_node(mchn);
	// super important que ce soit juste le token après le crnt_redir en debut de fonction psk l'etat de la machine peut changer entre temps
	node->right = generate_simple_command(mchn);
	return(node);
}
t_ast	*generate_pipe_node(t_ast_machine *mchn)
{
	t_ast		*node;

	mchn->crnt_pipe = find_first_pipe(mchn->crnt_pipe);
	if (mchn->crnt_pipe == NULL)
		return (generate_redir_node(mchn));
	node = generate_node(token_to_node_type(((t_token *)(mchn->crnt_pipe->content))->type), mchn->crnt_pipe->content);
	mchn->crnt_pipe = mchn->crnt_pipe->next;
	node->left = generate_pipe_node(mchn);
	/*if (advance_token(mchn) == NULL)*/
	/*	return (node);*/
	/*if (token_to_node_type(mchn->crnt_tkn->type) != 0)*/
	/*{*/
	/*	if (advance_token(mchn) == NULL)*/
	/*		return (node);*/
	/**/
	/*}*/
	node->right = generate_redir_node(mchn);
	return (node);
}

t_ast	*generate_full_ast(t_token_list **list)
{
	t_ast *node;
	t_ast_machine	*mchn;

	mchn = create_ast_machine(*list);
	if (mchn == NULL)
		return (NULL);
	node = generate_pipe_node(mchn);
	print_ast(node);
	free_ast_machine(&mchn);
	free_ast(&node);
	return (node);
}
