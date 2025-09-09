/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:31:39 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/09 16:27:34 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"
#include "struct.h"
#include "context.h"

void	init_exec_data(t_exec_data *exec_data, t_ast *root)
{
	int	i;

	i = 0;
	*exec_data = (t_exec_data){0};
	exec_data->envp = (context_read())->env;
	exec_data->root = root;
	exec_data->nb_cmds = count_commands(root);
	exec_data->cmds = malloc(sizeof(t_cmds)
			* (long unsigned int)(exec_data->nb_cmds));
	if (!exec_data->cmds)
		ft_fatal_error(exec_data, "minishell: malloc failed\n", 1, &free_exec);
	while (i < exec_data->nb_cmds)
	{
		exec_data->cmds[i].cmd = NULL;
		exec_data->cmds[i].redir = NULL;
		exec_data->cmds[i].path = NULL;
		i++;
	}
	exit_code_update(0);
}

void	fill_one_cmd(t_exec_data *exec_data, t_cmd cmd, int *i)
{
	int	count;
	int	j;

	j = 0;
	count = count_nbr_args(cmd.args);
	exec_data->cmds[*i].cmd = malloc(sizeof(char *)
			* (long unsigned int)(count + 1));
	if (!exec_data->cmds[*i].cmd)
		ft_fatal_error(exec_data, "minishell: malloc failed\n", 1, &free_exec);
	while (cmd.args[j])
	{
		exec_data->cmds[*i].cmd[j] = cmd.args[j];
		j++;
	}
	exec_data->cmds[*i].redir = cmd.redir;
	exec_data->cmds[*i].cmd[j] = NULL;
}

void	fill_cmds(t_exec_data *exec_data, t_ast *ast, int *i)
{
	if (!ast)
		return ;
	if (ast->type == NODE_PIPE)
	{
		fill_cmds(exec_data, ast->s_pipe.left, i);
		fill_cmds(exec_data, ast->s_pipe.right, i);
	}
	else if (ast->type == NODE_COMMAND)
	{
		fill_one_cmd(exec_data, ast->cmd, i);
		(*i)++;
	}
}

void	ast_to_cmds(t_exec_data *exec_data, t_ast *root)
{
	int	i;

	i = 0;
	init_exec_data(exec_data, root);
	fill_cmds(exec_data, root, &i);
}
