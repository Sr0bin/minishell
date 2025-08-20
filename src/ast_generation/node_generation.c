/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_generation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:41:45 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/20 15:51:05 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*node_cmd_create(t_token_list *tkn_lst)
{
	t_ast	*node;
	t_cmd	cmd;

	cmd = cmd_create(tkn_lst);
	node = generate_node(NODE_COMMAND, cmd);
	return (node);
}

t_ast	*node_pipe_create(t_token_list *tkn_lst, t_token_list *last_pipe)
{
	t_ast			*node;
	t_token_list	*crnt_pipe_ptr;
	t_node_type		node_type;

	if (!tkn_lst || tkn_lst == last_pipe)
		return (node_cmd_create(tkn_lst));
	crnt_pipe_ptr = pipe_find_n(tkn_lst, pipe_count(tkn_lst, last_pipe));
	if (crnt_pipe_ptr == NULL)
		return (node_cmd_create(tkn_lst));
	node_type = token_to_node_type(((t_token *)(crnt_pipe_ptr->content))->type);
	node = generate_node(node_type, (t_cmd){0});
	node->s_pipe.left = node_pipe_create(tkn_lst, crnt_pipe_ptr);
	if (crnt_pipe_ptr->next != NULL)
		node->s_pipe.right = node_cmd_create(crnt_pipe_ptr->next);
	return (node);
}
