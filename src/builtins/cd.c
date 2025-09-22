/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:49:30 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/22 11:13:25 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

int	update_env(t_exec_data *exec_data, const char *key, const char *value)
{
	t_env	*env;
	t_var	*var;

	if (!value)
		return (-1);
	env = exec_data->envp;
	while (env)
	{
		var = (t_var *)env->content;
		if (ft_strcmp(var->key, key) == 0)
		{
			free(var->value);
			var->value = ft_strdup(value);
			if (!var->value)
			{
				ft_error("minishell: ft_strdup failed\n", 1);
				return (-1);
			}
			return (0);
		}
		env = env->next;
	}
	return (0);
}

int ft_cd(t_exec_data *exec_data, t_cmds cmd)
{
	char *path;
	char *old_pwd;
	char *new_pwd;

	if (!cmd.cmd[1])
	{
		path = get_env_value(exec_data, "HOME");
		if (!path || ft_strcmp(path, "") == 0)
		{
			ft_error("minishell: cd: HOME not set\n", 1);
			return (-1);
		}
	}
	else if (ft_strcmp(cmd.cmd[1], "-") == 0)
	{
		path = get_env_value(exec_data, "OLDPWD");
		if (!path || ft_strcmp(path, "") == 0)
		{
			ft_error("minishell: cd: OLDPWD not set\n", 1);
			return (-1);
		}
	}
	else
		path = cmd.cmd[1];
	old_pwd = get_env_value(exec_data, "PWD");
	if (chdir(path) == -1)
	{
		ft_error("minishell: cd", 1);
		return (-1);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		ft_error("minishell: error retrieving current directory\n", 2);
		return(-1);
	}
	if (old_pwd)
	{
		if (update_env(exec_data, "OLDPWD", old_pwd) == -1)
		{
			free(new_pwd);
			return (-1);
		}
	}
	if (update_env(exec_data, "PWD", new_pwd) == -1)
	{
		free(new_pwd);
		return (-1);
	}
	if (cmd.cmd[1] && ft_strcmp(cmd.cmd[1], "-") == 0)
		printf("%s\n", new_pwd);
	free(new_pwd);
	return (0);
}
