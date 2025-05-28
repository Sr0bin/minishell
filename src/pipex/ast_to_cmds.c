/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:31:39 by lserodon          #+#    #+#             */
/*   Updated: 2025/05/28 14:51:03 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"


#include <stdio.h>

void print_cmds(t_utils *utils)
{
	if (!utils || !utils->cmds)
		return;

	printf("=== Commandes ===\n");
	for (int i = 0; i < utils->nb_cmds; i++)
	{
		t_cmds *cmd = &utils->cmds[i];

		printf("Commande #%d :\n", i + 1);

		// cmd
		if (cmd->cmd)
		{
			printf("  Arguments : ");
			for (int j = 0; cmd->cmd[j]; j++)
				printf("\"%s\" ", cmd->cmd[j]);
			printf("\n");
		}
		else
			printf("  Arguments : (null)\n");

		// path
		printf("  Path      : %s\n", cmd->path ? cmd->path : "(null)");

		// redirections
		printf("  fd_in     : %s\n", cmd->fd_in ? cmd->fd_in : "(stdin par défaut)");
		printf("  fd_out    : %s\n", cmd->fd_out ? cmd->fd_out : "(stdout par défaut)");

		printf("\n");
	}
}


int	count_commands(t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (1);
	else if (node->type == NODE_PIPE)
		return (count_commands(node->left) + count_commands(node->right));
	else if (node->type == NODE_REDIR_APPEND || node->type == NODE_REDIR_IN || node->type == NODE_REDIR_OUT)
		return (count_commands(node->left));
	return (0);
}

int	count_nbr_args(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		i++;
		token = token->next;
	}
	return (i);
}

void	fill_one_cmd(t_utils *utils, t_token *token, int *i)
{
	int	count;
	int	j;

	j = 0;
	count = count_nbr_args(token);
	utils->cmds[*i].cmd = malloc(sizeof(char *) * (long unsigned int)(count + 1));
	if (!utils->cmds[*i].cmd)
		return ;
	while (token)
	{
		utils->cmds[*i].cmd[j] = ft_strdup(token->content);
		token = token->next;
		j++;
	}
	utils->cmds[*i].cmd[j] = NULL;
}

void	fill_redir(t_utils *utils, t_node_type redir_type, t_ast_node *node, int *i)
{
	if (redir_type == NODE_REDIR_IN)
		utils->cmds[*i].fd_in = ft_strdup(node->token_list->content);
	else if (redir_type == NODE_REDIR_OUT)
		utils->cmds[*i].fd_out = ft_strdup(node->token_list->content);
}

void	fill_cmds(t_utils *utils, t_ast_node *node, int *i)
{
	if (!node)
		return;
	if (node->type == NODE_PIPE)
	{
		fill_cmds(utils, node->left, i);
		fill_cmds(utils, node->right, i);			
	}
	else if (node->type == NODE_REDIR_IN || node->type == NODE_REDIR_OUT)
	{	
		fill_redir(utils, node->type, node->right, i);
		fill_cmds(utils, node->left, i);
	}
	else if (node->type == NODE_COMMAND)
	{
		fill_one_cmd(utils, node->token_list, i);
		(*i)++;
	}
}

void	ast_to_cmds(t_utils *utils, t_ast_node *root)
{
	int	i;
	
	i = 0;
	init_utils(utils, root);
	fill_cmds(utils, root, &i);
}