/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multipipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:14:56 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/20 21:36:37 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes/multipipes.h"

void	exec_single_cmd(t_exec_data *exec_data)
{
	pid_t	pid;
	int 	status;
	
	pid = fork();
	if (pid == -1)
		ft_error(exec_data, "minishell: fork failed", 1);
	else if (pid == 0)
		exec_cmd(exec_data, 0);
	else
		waitpid(pid, &status, 0);
	free_exec_data(exec_data);
	//exit (0);
}

void	exec(t_ast *root, char **envp)
{
	t_exec_data	*exec_data;

	exec_data = malloc(sizeof(t_exec_data));
	if (!exec_data)
		ft_error(exec_data, "minishell: malloc failed", 1);
	*exec_data = (t_exec_data){0};
	exec_data->envp = envp;
	ast_to_cmds(exec_data, root);
	if (exec_data->nb_cmds == 1)
		exec_single_cmd(exec_data);
	else
	{
		init_pipes(exec_data);
		exec_pipex(exec_data);
	}
}
