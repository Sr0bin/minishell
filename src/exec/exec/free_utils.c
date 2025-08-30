/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:04:52 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/30 13:58:26 by lserodon         ###   ########.fr       */
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
	while (current)
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

	i = 0;
	while (i < exec_data->nb_cmds)
	{
		free(exec_data->cmds[i].cmd);
		if (!exec_data->cmds[i].path)
			free(exec_data->cmds[i].path);
		i++;
	}
	free(exec_data->cmds);
}

void	free_fds(int **fd, int nb_cmbs)
{
	int	i;

	i = 0;
	if (!fd)
		return ;
	while (i < nb_cmbs - 1)
	{
		if (fd[i])
			free(fd[i]);
		i++;
	}
	free(fd);
}

void	free_exec_data(t_exec_data *exec_data)
{
	if (!exec_data)
		exit (1);
	if (exec_data->root)
		ast_destroy(&exec_data->root);
	if (exec_data->tkn_list)
		token_list_destroy(exec_data->tkn_list);
	if (exec_data->cmds)
		free_cmds(exec_data);
	if (exec_data->fd)
		free_fds(exec_data->fd, exec_data->nb_cmds);
	free (exec_data);
}
