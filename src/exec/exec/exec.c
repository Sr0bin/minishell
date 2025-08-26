/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:14:56 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/26 17:23:04 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_generation/ast.h"
#include "parsing/token.h"
#include "exec/multipipes.h"

void	exec(t_ast *root, t_token_list **tkn_lst, t_env	*env)
{
	t_exec_data	*exec_data;

	exec_data = malloc(sizeof(t_exec_data));
	if (!exec_data)
		ft_error(exec_data, "minishell: malloc failed", 1);
	*exec_data = (t_exec_data){0};
	exec_data->envp = env;
	ast_to_cmds(exec_data, root);
	ast_destroy(&root);
	token_list_destroy(tkn_lst);
	if (exec_data->nb_cmds == 1)
		exec_single_cmd(exec_data, 0);
	else
	{
		init_pipes(exec_data);
		exec_pipex(exec_data);
	}
	free_exec_data(exec_data);
}
