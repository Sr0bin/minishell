/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:25:17 by rorollin          #+#    #+#             */
/*   Updated: 2025/07/19 19:13:02 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"



t_ast	*generate_simple_command(t_token_list *list)
{
	t_ast	*node;

	node = generate_node(NODE_COMMAND, NULL);
	if (node == NULL)
		return (NULL);
	node->left = generate_node(NODE_COMMAND, list->content);
	if (node->left == NULL)
	{
		free(node);
		return (NULL);
	}

	node->right = generate_node(NODE_COMMAND, list->next->content);
	if (node->right == NULL)
	{
		free(node->left);
		free(node);
		return (NULL);
	}
	return (node);
}

t_ast	*generate_redir_node(t_token_list *list)
{
	t_token_list	*iter;
	t_token_list			*token_redir;
	t_ast		*node;

	iter = list;
	if (list == NULL)
		return	(NULL);
	token_redir = find_first_redir(list);
	if (token_redir == NULL)
		return (generate_simple_command(list));
	node = generate_node(token_to_node_type(((t_token *) (token_redir->content))->type), token_redir->content);
	node->left = generate_simple_command




	return (node);

}

t_ast	*generate_full_ast(t_token_list **list)
{
	t_ast *node;
	t_token_list	*list_start;

	node = NULL;
	list_start = *list;
	free_token_only_list(list);
	return (node);
}
