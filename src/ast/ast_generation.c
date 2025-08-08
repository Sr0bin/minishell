/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:25:17 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/06 16:56:29 by rorollin         ###   ########.fr       */
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

t_ast	*generate_command_node(t_token_list *tkn_lst)

t_ast	*generate_simple_command(t_token_list *tkn_lst)
{
	t_ast	*node;

	node = generate_node(NODE_COMMAND, NULL);
	if (node == NULL)
		return (NULL);
	node->left = generate_node(NODE_COMMAND, tkn_lst->content);
	if (node->left == NULL)
	{
		free_node(&node);
		return (NULL);
	}
	if (tkn_lst->next != NULL && token_to_node_type(((t_token *)tkn_lst->content)->type) == 0)
	{
		tkn_lst = tkn_lst->next;
		node->right = generate_node(NODE_COMMAND, tkn_lst->content);
		if (node->right == NULL)
		{
			free_node(&(node->left));
			free_node(&node);
			return (NULL);
		}
		tkn_lst = tkn_lst->next;
		while (tkn_lst != NULL && token_to_node_type(((t_token *)tkn_lst->content)->type) == 0)
		{
			//TODO(rorollin): protection malloc
			ft_strcat(&(node->right->token->content), ((t_token *)tkn_lst->content)->content);
			free(tkn_lst->content);
			tkn_lst = tkn_lst->next;
		}
	}
	return (node);
}
/*t_ast	*generate_simple_command(t_ast_machine *mchn)*/
/*{*/
/*	t_ast	*node;*/
/**/
/*	print_ast_state(mchn, "generate_simple_command ENTRY");*/
/*	node = generate_node(NODE_COMMAND, NULL);*/
/*	if (node == NULL)*/
/*		return (NULL);*/
/*	node->left = generate_node(NODE_COMMAND, mchn->crnt_tkn);*/
/*	if (node->left == NULL)*/
/*	{*/
/*		free_node(&node);*/
/*		return (NULL);*/
/*	}*/
/*	if (advance_token(mchn) != NULL && token_to_node_type(mchn->crnt_tkn->type) == 0)*/
/*	{*/
/*		node->right = generate_node(NODE_COMMAND, mchn->crnt_tkn);*/
/*		if (node->right == NULL)*/
/*		{*/
/*			free_node(&(node->left));*/
/*			free_node(&node);*/
/*			return (NULL);*/
/*		}*/
/*		while (advance_token(mchn) != NULL && token_to_node_type(mchn->crnt_tkn->type) == 0)*/
/*		{*/
/*			ft_strcat(&(node->right->token->content), mchn->crnt_tkn->content);*/
/*			free(mchn->crnt_tkn);*/
/*		}*/
/*	}*/
/*	advance_token(mchn);*/
/*	return (node);*/
/*}*/

t_ast	*generate_redir_node(t_token_list *tkn_lst)
{
	t_ast	*node;
	t_token_list	*crnt_redir_ptr;

	crnt_redir_ptr = find_first_redir(tkn_lst);	
	if (crnt_redir_ptr == NULL)
		return (generate_simple_command(tkn_lst));
	node = generate_node(token_to_node_type(((t_token *)(crnt_redir_ptr->content))->type), crnt_redir_ptr->content);
	node->left = generate_redir_node(crnt_redir_ptr->next);
	if (crnt_redir_ptr->next != NULL)
		node->right = generate_node(NODE_FILE, crnt_redir_ptr->next->content);
	return (node);
}
/**/
/*t_ast	*generate_redir_node(t_ast_machine *mchn)*/
/*{*/
/*	t_ast	*node;*/
/*	t_token_list	*crnt_redir_ptr;*/
/**/
/*	crnt_redir_ptr = find_first_redir(mchn->crnt_tkn_lst);*/
/*	if (crnt_redir_ptr == NULL)*/
/*	{*/
/*		return (generate_simple_command(mchn->crnt_tkn_lst));*/
/*	}*/
/*	mchn->crnt_tkn_lst = crnt_redir_ptr->next;*/
/*	node = generate_node(token_to_node_type(((t_token *)(crnt_redir_ptr->content))->type), crnt_redir_ptr->content);*/
/*	node->left = generate_redir_node(mchn);*/
/*	if (crnt_redir_ptr->next != NULL)*/
/*		node->right = generate_node(NODE_FILE, crnt_redir_ptr->next->content);*/
/*	return(node);*/
/*}*/

t_ast	*generate_pipe_node(t_ast_machine *mchn)
{
	t_ast		*node;
	t_token_list	*crnt_pipe_ptr;

	/*print_ast_state(mchn, "generate_pipe_node ENTRY");*/
	crnt_pipe_ptr = find_first_pipe(mchn->crnt_tkn_lst);
	if (crnt_pipe_ptr == NULL)
		return (generate_redir_node(mchn->crnt_tkn_lst));
	mchn->crnt_tkn_lst = crnt_pipe_ptr->next;
	node = generate_node(token_to_node_type(((t_token *)(crnt_pipe_ptr->content))->type), crnt_pipe_ptr->content);
	node->left = generate_pipe_node(mchn);
	// super important que ce soit juste le token après le crnt_pipe en debut de fonction psk l'etat de la machine peut changer entre temps
	if (crnt_pipe_ptr->next != NULL)
		node->right = generate_redir_node(mchn->crnt_tkn_lst);
	return(node);
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
