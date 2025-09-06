/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:49:30 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/06 22:40:55 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

int		create_env_var(t_exec_data *exec_data, char *key, char *value)
{
	t_var	*new_var;
	t_list	*new_lst;

	new_var = malloc(sizeof(t_var));
	if (!new_var)
	{
		ft_error("minishell: malloc failed", 1);
		return (-1);
	}
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	if (!new_var->key || !new_var->value)
	{
		free_var(new_var);
		ft_error("minishell: ft_strdup failed", 1);
		return (-1);
	}
	new_lst = ft_lstnew(new_var);
	if (!new_lst)
	{
		free_var(new_var);
		ft_error("minishell: malloc failed", 1);
		return (-1);
	}
	ft_lstadd_back(&exec_data->envp, new_lst);
	return (0);
}

int	update_env(t_exec_data *exec_data, char *key, char *value)
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
				ft_error("minishell: ft_strdup failed", 1);
				return (-1);
			}
			return (0);
		}
		env = env->next;
	}
	if (create_env_var(exec_data, key, value) == -1)
		return (-1);
}

int	ft_cd(t_exec_data *exec_data, t_cmds cmd)
{
	char	*path;
	char	*new_pwd;
	char	*old_pwd;
	char	*pwd_value;
	int		count;

	old_pwd = NULL;
	path = NULL;
	new_pwd = NULL;
	count = count_nbr_args(cmd.cmd);
	if (count == 1)
	{
		path = get_env_value(exec_data, "HOME");
		if (!path)
		{
			ft_error("minishell: cd: HOME not set", 1);
			return (-1);
		}
	}
	else if (count == 2 && ft_strcmp(cmd.cmd[1], "-") == 0)
	{
		path = get_env_value(exec_data, "OLDPWD");
		if (!path)
		{
			ft_error("minishell: cd : OLDPWD not set", 1);
			return (-1);
		}
	}
	else if (count > 2)
	{
		ft_error("minishell: too many arguments", 1);
		return (-1);
	}
	else
		path = cmd.cmd[1];
	pwd_value = get_env_value(exec_data, "PWD");
	if (pwd_value)
	{
		old_pwd = ft_strdup(pwd_value);
		if (!old_pwd)
		{
			ft_error("minishell: error retrieving current directory", 2);
			return (-1);
		}
	}
	if (chdir(path) == -1)
	{
		ft_error("minishell: cd", 1);
		free(old_pwd);
		return (-1);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		ft_error("minishell: error retrieving current directory", 2);
		if (old_pwd && chdir(old_pwd) == -1)
			ft_error("minishell: cannot access parent directories", 2);
		free(old_pwd);
		return (-1);
	}
	if (update_env(exec_data, "PWD", new_pwd) == -1)
		return (-1);
	free(new_pwd);
	if (old_pwd)
	{
		if (update_env(exec_data, "OLDPWD", old_pwd) == -1)
			return (-1);
	}
	if (count == 2 && ft_strcmp(cmd.cmd[1], "-") == 0)
		ft_pwd(exec_data);
	free(old_pwd);
	return (0);
}
