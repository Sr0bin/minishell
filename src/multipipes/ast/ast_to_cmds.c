/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:31:39 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/23 12:54:14 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes/multipipes.h"

void	init_utils(t_utils *utils, t_ast_node *root)
{
	int	i;

	i = 0;
	utils->nb_cmds = count_commands(root);
	utils->cmds = malloc(sizeof(t_cmds)
			* (long unsigned int)(utils->nb_cmds + 1));
	if (!utils->cmds)
		ft_error(utils, "minishell : malloc failed", 1);
	while (i < utils->nb_cmds)
	{
		utils->cmds[i].cmd = NULL;
		utils->cmds[i].fd_in.fd = NULL;
		utils->cmds[i].fd_out.fd = NULL;
		i++;
	}
}

void	fill_one_cmd(t_utils *utils, t_token *token, int *i)
{
	int	count;
	int	j;

	j = 0;
	count = count_nbr_args(token);
	utils->cmds[*i].cmd = malloc(sizeof(char *)
			* (long unsigned int)(count + 1));
	if (!utils->cmds[*i].cmd)
		ft_error(utils, "minishell : malloc failed", 1);
	while (token)
	{
		utils->cmds[*i].cmd[j] = ft_strdup(token->content);
		if (!utils->cmds[*i].cmd[j])
			ft_error(utils, "minishell : strdup failed", 1);
		token = token->next;
		j++;
	}
	utils->cmds[*i].cmd[j] = NULL;
}

void	fill_redir(t_utils *utils, t_node_type redir, t_ast_node *node, int *i)
{
	if (redir == NODE_REDIR_IN)
	{
		free(utils->cmds[*i].fd_in.fd);
		utils->cmds[*i].fd_in.redir_type = REDIR_INPUT;
		utils->cmds[*i].fd_in.fd = ft_strdup(node->token_list->content);
		if (!utils->cmds[*i].fd_in.fd
			|| access(utils->cmds[*i].fd_in.fd, F_OK | R_OK) == -1)
			ft_error(utils, "minishell: fd_in failed", 1);
	}
	else if (redir == NODE_REDIR_OUT)
	{
		free(utils->cmds[*i].fd_out.fd);
		utils->cmds[*i].fd_out.redir_type = REDIR_OUTPUT;
		utils->cmds[*i].fd_out.fd = ft_strdup(node->token_list->content);
		if (!utils->cmds[*i].fd_out.fd)
			ft_error(utils, "minishell : strdup failed", 1);
	}
	else if (redir == NODE_REDIR_APPEND)
	{
		free(utils->cmds[*i].fd_out.fd);
		utils->cmds[*i].fd_out.redir_type = REDIR_APPEND;
		utils->cmds[*i].fd_out.fd = ft_strdup(node->token_list->content);
		if (!utils->cmds[*i].fd_out.fd)
			ft_error(utils, "minishell : strdup failed", 1);
	}
}

void	fill_cmds(t_utils *utils, t_ast_node *node, int *i)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		fill_cmds(utils, node->left, i);
		fill_cmds(utils, node->right, i);
	}
	else if (node->type == NODE_REDIR_IN || node->type == NODE_REDIR_OUT
		|| node->type == NODE_REDIR_APPEND)
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
