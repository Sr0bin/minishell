/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multipipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:14:56 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/23 13:31:53 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes/multipipes.h"

void	exec_single_cmd(t_utils *utils)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error(utils, "minishell: fork failed", 1);
	else if (pid == 0)
		exec_cmd(utils, 0);
	free_utils(utils);
	exit (0);
}

void	exec(t_ast_node *root, char **envp)
{
	t_utils	*utils;

	utils = malloc(sizeof(t_utils));
	if (!utils)
		ft_error(utils, "minishell: malloc failed", 1);
	*utils = (t_utils){0};
	utils->envp = envp;
	ast_to_cmds(utils, root);
	if (utils->nb_cmds == 1)
		exec_single_cmd(utils);
	else
	{
		init_pipes(utils);
		exec_pipex(utils);
	}
}
