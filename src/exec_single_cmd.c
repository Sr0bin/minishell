/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:06:10 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/17 10:20:34 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/exec.h"

void	exec_single_cmd(t_ast_node *root, char	**envp)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		ft_error(cmd, "minishell: malloc", 1);
	*cmd = (t_cmd){0};
	cmd->envp = envp;
	init_cmd(cmd, root);
	exec_cmd(cmd);
}
