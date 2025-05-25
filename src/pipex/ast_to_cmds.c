/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:31:39 by lserodon          #+#    #+#             */
/*   Updated: 2025/05/24 09:52:13 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"


int	count_commands(t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (1);
	else if (node->type == NODE_PIPE)
		return (count_commands(node->left) + count_commands(node->right));
	return (0);
}

int	is_next_of_redir(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == TOKEN_HEREDOC || token->type == TOKEN_REDIR_APPEND ||
		token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT)
		return (1);
	return (0);
}

int	count_nbr_args(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == TOKEN_WORD && !is_next_of_redir(token->prev))
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
	utils->cmds[*i].fd_in = NULL;
	utils->cmds[*i].fd_out = NULL;
	utils->cmds[*i].cmd = malloc(sizeof(char *) * (long unsigned int)(count + 1));
	if (!utils->cmds[*i].cmd)
		return ;
	while (token)
	{
		if (token->type == TOKEN_WORD && !is_next_of_redir(token->prev))
		{	
			utils->cmds[*i].cmd[j] = ft_strdup(token->content);
			j++;
		}
		else if (token->type == TOKEN_REDIR_IN && token->next)
		{
			utils->cmds[*i].fd_in = ft_strdup(token->next->content);
			token = token->next;
		}
		else if (token->type == TOKEN_REDIR_OUT && token->next)
		{
			utils->cmds[*i].fd_out = ft_strdup(token->next->content);
			token = token->next;
		}
		token = token->next;
	}
	utils->cmds[*i].cmd[j] = NULL;
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