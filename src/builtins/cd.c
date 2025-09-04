/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:49:30 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/04 16:35:52 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

void	update_env(t_exec_data *exec_data, char *key, char *value)
{
	t_env	*env;
	t_var	*var;

	if (!value)
		return ;
	env = exec_data->envp;
	while (env)
	{
		var = (t_var *)env->content;
		if (ft_strcmp(var->key, key) == 0)
		{
			free(var->value);
			var->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
}

int	ft_cd(t_exec_data *exec_data, t_cmds cmd)
{
	char	*path;
	char	*new_pwd;
	char	*old_pwd;
	int		count;

	count = count_nbr_args(cmd.cmd);
	if (count == 1)
		path = get_env_value(exec_data, "HOME");
	else if (count == 2 && ft_strcmp(cmd.cmd[1], "-") == 0)
		path = get_env_value(exec_data, "OLDPWD");
	else if (count > 2)
	{
		ft_error("too many arguments", 1);
		return (-1);
	}
	else
		path = cmd.cmd[1];
	old_pwd = ft_strdup(get_env_value(exec_data, "PWD"));
	if (!old_pwd)
	{
		ft_error("error retrieving current directory", 2);
		return (-1);
	}
	if (chdir(path) == -1)
		ft_error("cd: no such file or directory", 1);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		ft_error("error retrieving current directory", 2);
		return (-1);
	}
	update_env(exec_data, "PWD", new_pwd);
	if (old_pwd)
		update_env(exec_data, "OLDPWD", old_pwd);
	if (count == 2 && ft_strcmp(cmd.cmd[1], "-") == 0)
		ft_pwd(exec_data);
	free(new_pwd);
	free(old_pwd);
	return (0);
}
