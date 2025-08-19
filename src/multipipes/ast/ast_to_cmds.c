/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:31:39 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/19 10:43:56 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes/multipipes.h"
#include "../struct.h"

void	init_exec_data(t_exec_data *exec_data, t_ast_node *root)
{
	int	i;

	i = 0;
	exec_data->nb_cmds = count_commands(root);
	exec_data->cmds = malloc(sizeof(t_cmds)
			* (long unsigned int)(exec_data->nb_cmds + 1));
	if (!exec_data->cmds)
		ft_error(exec_data, "minishell : malloc failed", 1);
	while (i < exec_data->nb_cmds)
	{
		exec_data->cmds[i].cmd = NULL;
		exec_data->cmds[i].redir = NULL;
		i++;
	}
}

void	fill_one_cmd(t_exec_data *exec_data, t_token *token, int *i)
{
	int	j;
	int count;

	j = 0;
	count = count_nbr_args(token);
	exec_data->cmds[*i].cmd = malloc(sizeof(char *)
			* (long unsigned int)(count + 1));
	if (!exec_data->cmds[*i].cmd)
		ft_error(exec_data, "minishell : malloc failed", 1);
	while (token)
	{
		exec_data->cmds[*i].redir = 
		exec_data->cmds[*i].cmd[j] = ft_strdup(token->content);
		if (!exec_data->cmds[*i].cmd[j])
			ft_error(exec_data, "minishell : strdup failed", 1);
		token = token->next;
		j++;
	}
	exec_data->cmds[*i].cmd[j] = NULL;
}

void	fill_cmds(t_exec_data *exec_data, t_ast *ast, int *i)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		fill_cmds(exec_data, node->left, i);
		fill_cmds(exec_data, node->right, i);
	}
	else if (node->type == NODE_COMMAND)
	{
		fill_one_cmd(exec_data, node->token_list, i);
		(*i)++;
	}
}

void	ast_to_cmds(t_exec_data *exec_data, t_ast_node *root)
{
	int	i;

	i = 0;
	init_exec_data(exec_data, root);
	fill_cmds(exec_data, root, &i);
}
