/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:36:39 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/05 12:08:34 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"

char	*get_env_path( t_exec_data *exec_data)
{
	t_var	*var;
	t_list	*tmp;
	char	*value;

	tmp = exec_data->envp;
	value = NULL;
	while (tmp)
	{
		var = (t_var *)tmp->content;
		if (ft_strcmp(var->key, "PATH") == 0)
		{
			if (!var->value)
				ft_fatal_error(exec_data, "minishell: ft_strdup failed", 1, &free_exec);
			value = ft_strdup(var->value);
			if (!value)
				ft_fatal_error(exec_data, "minishell: ft_strdup failed", 1, &free_exec);
			return (value);
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
		ft_fatal_error(exec_data, "minishell: missing PATH", 1, &free_exec);
	path_array = ft_split(path, ':');
	free(path);
	if (!path_array)
		ft_fatal_error(exec_data, "minishell: ft_split failed", 1, &free_exec);
	return (path_array);
}

char	*build_cmd_path(t_exec_data *exec_data, char *dir, int i)
{
	char	*tmp_path;
	char	*cmd_path;

	tmp_path = ft_strjoin(dir, "/");
	if (!tmp_path)
		ft_fatal_error(exec_data, "minishell: ft_strjoin failed", 1, &free_exec);
	cmd_path = ft_strjoin(tmp_path, exec_data->cmds[i].cmd[0]);
	free(tmp_path);
	if (!cmd_path)
		ft_fatal_error(exec_data, "minishell: ft_strjoin failed", 1, &free_exec);
	return (cmd_path);
}

char	*check_access(t_exec_data *exec_data, char **array, char *path)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
		{
			free_array(array);
			return (path);
		}
		else
		{
			free_array(array);
			free(path);
			ft_fatal_error(exec_data, "minishell: permission denied", 1, &free_exec);
		}
	}
	return (NULL);
}

char	*find_path(t_exec_data *exec_data, int i)
{
	char	**path_array;
	char	*cmd_path;
	char	*tmp;
	int		j;

	path_array = get_path_array(exec_data);
	cmd_path = NULL;
	j = 0;
	while (path_array[j])
	{
		cmd_path = build_cmd_path(exec_data, path_array[j], i);
		tmp = check_access(exec_data, path_array, cmd_path);
		if (tmp)
			return (tmp);
		free(cmd_path);
		j++;
	}
	free_array(path_array);
	return (NULL);
}
