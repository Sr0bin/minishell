/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:36:39 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/28 18:33:20 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/multipipes.h"

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

char *get_env_value(t_exec_data *exec_data, char *key)
{
	t_var	*var;
	t_env	*current;

	current = exec_data->envp;
	while (current)
	{
		var = (t_var *)current->content;
		if (ft_strcmp(var->key, key) == 0)
			return(var->value);
		current = current->next;
	}
	return (NULL);
}

char	*get_env_path( t_exec_data *exec_data)
{
	t_var	*var;
	t_list	*tmp;

	tmp = exec_data->envp;
	while (tmp)
	{
		var = (t_var *)tmp->content;
		if (ft_strcmp(var->key, "PATH") == 0)
		{
			if (!var->value)
				ft_error(exec_data, "minishell: PATH is empty", 127);
			return (ft_strdup(var->value));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	**get_path_array(t_exec_data *exec_data)
{
	char	*path;
	char	**path_array;

	path = get_env_path(exec_data);
	if (!path)
		ft_error(exec_data, "minishell: missing PATH", 127);
	path_array = ft_split(path, ':');
	free(path);
	if (!path_array)
		ft_error(exec_data, "minishell: ft_split", 1);
	return (path_array);
}

char	*build_cmd_path(t_exec_data *exec_data, char *dir, int i)
{
	char	*tmp_path;
	char	*cmd_path;

	tmp_path = ft_strjoin(dir, "/");
	if (!tmp_path)
		ft_error(exec_data, "minishell: ft_strjoin", 1);
	cmd_path = ft_strjoin(tmp_path, exec_data->cmds[i].cmd[0]);
	free(tmp_path);
	if (!cmd_path)
		ft_error(exec_data, "minishell: ft_strjoin", 1);
	return (cmd_path);
}

char	*find_path(t_exec_data *exec_data, int i)
{
	char	**path_array;
	char	*cmd_path;
	int		j;

	path_array = get_path_array(exec_data);
	cmd_path = NULL;
	j = 0;
	while (path_array[j])
	{
		cmd_path = build_cmd_path(exec_data, path_array[j], i);
		if (access(cmd_path, F_OK) == 0)
		{
			if (access(cmd_path, X_OK) == 0)
			{
				free_array(path_array);
				return (cmd_path);
			}
			else
			{
				free_array(path_array);
				ft_error(exec_data, "minishell: Permission denied", 126);
			}
		}
		free(cmd_path);
		j++;
	}
	free_array(path_array);
	return (NULL);
}
