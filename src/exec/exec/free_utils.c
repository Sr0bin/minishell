/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:04:52 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/08 18:25:03 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_envp(t_env	*env)
{
	t_var	*var;
	t_env	*current;
	t_env	*tmp;

	current = env;
	while (current != NULL)
	{
		var = (t_var *)current->content;
		free(var->key);
		free(var->value);
		free(var);
		tmp = current;
		current = current->next;
		free(tmp);
	}
}

void	free_cmds(t_exec_data *exec_data)
{
	int	i;
	t_cmds	crnt_cmd;

	i = 0;
	while (i < exec_data->nb_cmds)
	{
		crnt_cmd = exec_data->cmds[i];
		free(crnt_cmd.cmd);
		if (crnt_cmd.path != NULL)
			free(crnt_cmd.path);
		i++;
	}
	free(exec_data->cmds);
}

void	free_fds(int **fd, int nb_cmds)
{
	int	i;

	i = 0;
	if (!fd)
		return ;
	if (nb_cmds == 1)
	{
		free(fd[0]);
	}
	else
	{
		while (i < nb_cmds - 1)
		{
			if (fd[i])
			free(fd[i]);
			i++;
		}
	}
	free(fd);
}

void	free_exec_data(t_exec_data *exec_data)
{
	if (!exec_data)
		exit (1);
	if (exec_data->root != NULL)
		ast_destroy(&exec_data->root);
	if (exec_data->cmds != NULL)
		free_cmds(exec_data);
	if (exec_data->fd != NULL)
		free_fds(exec_data->fd, exec_data->nb_cmds);
	free (exec_data);
}
