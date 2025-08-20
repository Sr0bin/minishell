/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:36:39 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/20 10:07:09 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes/multipipes.h"

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

char	*get_env_path( t_exec_data *exec_data, char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
			if (!path)
				ft_error(exec_data, "minishell: malloc", 1);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	**get_path_array(t_exec_data *exec_data)
{
	char	*path;
	char	**path_array;

	path = get_env_path(exec_data, exec_data->envp);
	if (!path)
		ft_error(exec_data, "minishell: missing PATH", 127);
	path_array = ft_split(path, ':');
	free(path);
	if (!path_array)
		ft_error(exec_data, "minishell: ft_split", 1);
	return (path_array);
}

char	*build_cmd_path(t_exec_data *exec_data, char *dir)
{
	char	*tmp_path;
	char	*cmd_path;

	tmp_path = ft_strjoin(dir, "/");
	if (!tmp_path)
		ft_error(exec_data, "minishell: ft_strjoin", 1);
	cmd_path = ft_strjoin(tmp_path, exec_data->cmds->cmd[0]);
	free(tmp_path);
	if (!cmd_path)
		ft_error(exec_data, "minishell: ft_strjoin", 1);
	return (cmd_path);
}

char	*find_path(t_exec_data *exec_data)
{
	char	**path_array;
	char	*cmd_path;
	int		j;

	path_array = get_path_array(exec_data);
	cmd_path = NULL;
	j = 0;
	while (path_array[j])
	{
		cmd_path = build_cmd_path(exec_data, path_array[j]);
		if (access(cmd_path, X_OK) == 0)
		{
			free_array(path_array);
			return (cmd_path);
		}
		free(cmd_path);
		j++;
	}
	free_array(path_array);
	return (NULL);
}
