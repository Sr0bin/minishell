/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:07:11 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/17 10:20:08 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/exec.h"

int	count_nbr_args(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		count++;
		token = token->next;
	}
	return (count);
}

void	fill_redir(t_cmd *cmd, t_node_type redir, t_ast_node *node)
{
	if (redir == NODE_REDIR_IN)
	{
		free(cmd->fd_in.fd);
		cmd->fd_in.redir_type = REDIR_INPUT;
		cmd->fd_in.fd = ft_strdup(node->token_list->content);
		if (!cmd->fd_in.fd || access(cmd->fd_in.fd, F_OK | R_OK) == -1)
			ft_error(cmd, "minishell: fd_in", 1);
	}
	else if (redir == NODE_REDIR_OUT)
	{
		free(cmd->fd_out.fd);
		cmd->fd_out.redir_type = REDIR_OUTPUT;
		cmd->fd_out.fd = ft_strdup(node->token_list->content);
		if (!cmd->fd_out.fd)
			ft_error(cmd, "minishell: ft_strdup", 1);
	}
	else if (redir == NODE_REDIR_APPEND)
	{
		free(cmd->fd_out.fd);
		cmd->fd_out.redir_type = REDIR_APPEND;
		cmd->fd_out.fd = ft_strdup(node->token_list->content);
		if (!cmd->fd_out.fd)
			ft_error(cmd, "minishell: ft_strdup", 1);
	}
}

void	fill_cmd(t_cmd *cmd, t_token *token)
{
	int	i;
	int	count;

	i = 0;
	count = count_nbr_args(token);
	cmd->cmd = malloc(sizeof(char *) * (long unsigned int)(count + 1));
	if (!cmd->cmd)
		ft_error(cmd, "minishell: malloc", 1);
	while (token)
	{
		cmd->cmd[i] = ft_strdup(token->content);
		if (!cmd->cmd[i])
			ft_error(cmd, "minishell: malloc", 1);
		i++;
		token = token->next;
	}
	cmd->cmd[i] = NULL;
}

void	init_cmd(t_cmd *cmd, t_ast_node *node)
{
	if (!node)
		return ;
	else if (node->type == NODE_REDIR_IN || node->type == NODE_REDIR_OUT
		|| node->type == NODE_REDIR_APPEND)
	{
		fill_redir(cmd, node->type, node->right);
		init_cmd(cmd, node->left);
	}
	else if (node->type == NODE_COMMAND)
		fill_cmd(cmd, node->token_list);
}
