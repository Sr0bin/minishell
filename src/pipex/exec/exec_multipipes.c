/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multipipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:14:56 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/03 15:02:47 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/multipipes.h"

void	exec_multipipes(t_ast_node *root, char **envp)
{
	t_utils	*utils;

	utils = malloc(sizeof(t_utils));
	if (!utils)
		ft_error(utils, "Error : malloc failed", 1);
	*utils = (t_utils){0};
	utils->envp = envp;
	ast_to_cmds(utils, root);
	init_pipes(utils);
	exec_pipex(utils);
}
