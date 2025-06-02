/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:36:39 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/02 12:17:22 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/multipipes.h"

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

char	*get_env_path(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*find_path(char **envp, char *cmd)
{
	char	*path;
	char	*tmp_path;
	char	*cmd_path;
	char	**path_array;
	int		i;

	path = get_env_path(envp);
	path_array = ft_split(path, ':');
	free (path);
	i = -1;
	while (path_array[++i])
	{
		tmp_path = ft_strjoin(path_array[i], (char *)"/");
		cmd_path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(cmd_path, X_OK) == 0)
		{
			free_array(path_array);
			return (cmd_path);
		}
		free(cmd_path);
	}
	return (NULL);
}
