/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:14:56 by lserodon          #+#    #+#             */
/*   Updated: 2025/05/28 14:51:11 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

void	init_utils(t_utils *utils, t_ast_node *root)
{
	int	i;

	i = 0;
	utils->nb_cmds = count_commands(root);
	utils->cmds = malloc(sizeof(t_cmds) * (long unsigned int)utils->nb_cmds);
	if (!utils->cmds)
		return ;
	while (i < utils->nb_cmds)
	{
		utils->cmds[i].fd_in = NULL;
		utils->cmds[i].fd_out = NULL;
		i++;
	}
}

void	exec_multipipe(t_ast_node *root, char **envp)
{
	t_utils *utils;
	
	utils = malloc(sizeof(t_utils));
	if (!utils)
		return ;
	utils->envp = envp;
	ast_to_cmds(utils, root);
	init_pipes(utils);
	exec_pipex(utils);
}

