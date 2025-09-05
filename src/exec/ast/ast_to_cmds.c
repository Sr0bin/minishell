/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:31:39 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/05 11:06:01 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"
#include "struct.h"
#include "context.h"

int	init_exec_data(t_exec_data *exec_data, t_ast *root)
{
	int	i;

	i = 0;
	if ((exec_data->nb_cmds = count_commands(root)) == 0)
		return (-1);
	exec_data->cmds = malloc(sizeof(t_cmds)
			* (long unsigned int)(exec_data->nb_cmds));
	if (!exec_data->cmds)
	{
		ft_error("minishell: malloc failed", 1);
		return (-1);
	}
	while (i < exec_data->nb_cmds)
	{
		exec_data->cmds[i].cmd = NULL;
		exec_data->cmds[i].redir = NULL;
		exec_data->cmds[i].path = NULL;
		i++;
	}
	exit_code_update(0);
	return (0);
}

t_list	*fill_redir(t_cmd cmd)
{
	t_list	*new;
	t_redir	*new_redir;
	t_redir	*old_redir;

	if (!cmd.redir)
		return (NULL);
	old_redir = (t_redir *) cmd.redir->content;
	new = NULL;
	while (cmd.redir)
	{
		new_redir = malloc(sizeof(t_redir));
		if (!new_redir)
		{
			ft_error("minishell: malloc failed", 1);
			return (NULL);
		}
		new_redir->type = old_redir->type;
		if (new_redir->type == REDIR_HEREDOC)
			new_redir->s_heredoc.read = old_redir->s_heredoc.read;
		else
			new_redir->filename = ft_strdup(old_redir->filename);
		if (!new_redir->filename)
		{
			ft_error("minishell: ft_strdup failed", 1);
			return (NULL);
		}
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
	{
		ft_error("minishell: malloc failed", 1);
		return (-1);
	}
	while (cmd.args[j])
	{
		exec_data->cmds[*i].cmd[j] = cmd.args[j];
		j++;
	}
	exec_data->cmds[*i].redir = cmd.redir;
	exec_data->cmds[*i].cmd[j] = NULL;
	return (0);
}

int	fill_cmds(t_exec_data *exec_data, t_ast *ast, int *i)
{
	if (!ast)
		return (1);
	if (ast->type == NODE_PIPE)
	{
		if (fill_cmds(exec_data, ast->s_pipe.left, i) == -1)
			return (-1);
		if (fill_cmds(exec_data, ast->s_pipe.right, i) == -1)
			return (-1);
	}
	else if (ast->type == NODE_COMMAND)
	{
		if (fill_one_cmd(exec_data, ast->cmd, i) == -1)
			return (-1);
		(*i)++;
	}
	return (0);
}

int	ast_to_cmds(t_exec_data *exec_data, t_ast *root)
{
	int	i;

	i = 0;
	if (init_exec_data(exec_data, root) == -1)
		return (-1);
	if (fill_cmds(exec_data, root, &i) == -1)
		return (-1);
	return (0);
}
