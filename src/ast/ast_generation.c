/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:25:17 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/10 18:06:02 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "list.h"
#include "minishell.h"
#include <stdio.h>

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


void	*redir_destroy(t_redir_list **redir_list, t_redir **redir)
{
	ft_lstclear(redir_list, (void (*)) free_redir);
	free_redir(*redir);
	return (NULL);
}

t_redir_list	*redir_list_create(t_token_list *tkn_lst)
{
	t_token_list	*crnt_tkn;
	t_redir_list	*redir_list;
	t_redir_list	*list_temp;
	t_redir	*crnt_redir;

	
	
	redir_list = NULL;
	crnt_redir = NULL;
	crnt_tkn = redir_find_first(tkn_lst);
	if (crnt_tkn == NULL)
		return (NULL);
	crnt_redir = create_redir_token(crnt_tkn);
	redir_list = ft_lstnew(crnt_redir);
	if (redir_list == NULL)
		return (redir_destroy(&redir_list, &crnt_redir));
	crnt_tkn = redir_find_first(crnt_tkn->next);
	while (crnt_tkn != NULL)
	{
		crnt_redir = create_redir_token(crnt_tkn);
		list_temp = ft_lstnew(crnt_redir);
		if (crnt_redir == NULL || list_temp == NULL)
			return (redir_destroy(&redir_list, &crnt_redir));
		ft_lstadd_back(&redir_list, list_temp);
		crnt_tkn = redir_find_first(crnt_tkn->next);
	}
	return (redir_list);
}

t_cmd	cmd_create(t_token_list *tkn_lst)
{
	t_cmd	cmd;

	cmd.redir = redir_list_create(tkn_lst);
	cmd.path = ft_strdup(lst_to_tkn(tkn_lst)->content);
	cmd.args = NULL;
	cmd.envp = NULL;
	return (cmd);
}

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
	t_ast		*node;
	t_token_list	*crnt_pipe_ptr;

	crnt_pipe_ptr = pipe_find_n(tkn_lst, pipe_count(tkn_lst, last_pipe));
	if (crnt_pipe_ptr == NULL)
		return (node_cmd_create(tkn_lst));
	node = generate_node(token_to_node_type(((t_token *)(crnt_pipe_ptr->content))->type), (t_cmd){0});

	node->pipe.left = node_pipe_create(tkn_lst, crnt_pipe_ptr);
	/*node->pipe.left = node_pipe_create(tkn_lst, pipe_find_n(tkn_lst, pipe_count(tkn_lst, last_pipe) - 1));*/
	//!
	node->pipe.right = node_pipe_create(crnt_pipe_ptr->next, NULL);
	return (node);
}

t_ast	*ast_create(t_token_list **list)
{
	t_ast *node;

	node = node_pipe_create(*list, pipe_find_last(*list));
	return (node);
}
