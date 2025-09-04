/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:31:39 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/04 19:26:22 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"
#include "struct.h"
#include "context.h"

void	init_exec_data(t_exec_data *exec_data, t_ast *root)
{
	int	i;

	i = 0;
	exec_data->nb_cmds = count_commands(root);
	exec_data->cmds = malloc(sizeof(t_cmds)
			* (long unsigned int)(exec_data->nb_cmds));
	if (!exec_data->cmds)
		ft_fatal_error(exec_data, "malloc failed", 1, &free_exec);
	while (i < exec_data->nb_cmds)
	{
		exec_data->cmds[i].cmd = NULL;
		exec_data->cmds[i].redir = NULL;
		exec_data->cmds[i].path = NULL;
		i++;
	}
	exit_code_update(0);
}

t_list	*fill_redir(t_exec_data *exec_data, t_cmd cmd)
{
	t_list	*new;
	t_redir	*new_redir;
	t_redir	*old_redir;

	old_redir = (t_redir *) cmd.redir->content;
	if (!cmd.redir)
		return (NULL);
	new = NULL;
	while (cmd.redir)
	{
		new_redir = malloc(sizeof(t_redir));
		if (!new_redir)
			ft_fatal_error(exec_data, "malloc failed", 1, &free_exec);
		new_redir->type = old_redir->type;
		if (new_redir->type == REDIR_HEREDOC)
			new_redir->s_heredoc.read = old_redir->s_heredoc.read;
		else
			new_redir->filename = ft_strdup(old_redir->filename);
		if (!new_redir->filename)
			ft_fatal_error(exec_data, "strdup failed", 1, &free_exec);
		ft_lstadd_back(&new, ft_lstnew(new_redir));
		cmd.redir = cmd.redir->next;
	}
	return (new);
}

int	fill_one_cmd(t_exec_data *exec_data, t_cmd cmd, int *i)
{
	int	count;
	int	j;

	j = 0;
	count = count_nbr_args(cmd.args);
	exec_data->cmds[*i].cmd = malloc(sizeof(char *)
			* (long unsigned int)(count + 1));
	if (!exec_data->cmds[*i].cmd)
		ft_fatal_error(exec_data, "malloc failed", 1, &free_exec);
	while (cmd.args[j])
	{
		exec_data->cmds[*i].cmd[j] = cmd.args[j];
		if (!exec_data->cmds[*i].cmd[j])
			ft_fatal_error(exec_data, "strdup failed", 1, &free_exec);
		j++;
	}
	exec_data->cmds[*i].redir = cmd.redir;
	exec_data->cmds[*i].cmd[j] = NULL;
	return (0);
}

int	fill_cmds(t_exec_data *exec_data, t_ast *ast, int *i)
{
	if (!ast)
		return (-1);
	if (ast->type == NODE_PIPE)
	{
		fill_cmds(exec_data, ast->s_pipe.left, i);
		fill_cmds(exec_data, ast->s_pipe.right, i);
	}
	else if (ast->type == NODE_COMMAND)
	{
		if (fill_one_cmd(exec_data, ast->cmd, i) == 1)
			return (1);
		(*i)++;
	}
	return (0);
}

int	ast_to_cmds(t_exec_data *exec_data, t_ast *root)
{
	int	i;

	i = 0;
	init_exec_data(exec_data, root);
	if (fill_cmds(exec_data, root, &i) == 1)
		return (1);
	return (0);
}
