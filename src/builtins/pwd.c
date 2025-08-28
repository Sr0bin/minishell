/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:57:41 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/28 08:57:26 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include <errno.h>

int	ft_pwd(t_exec_data *exec_data)
{
	char	*buffer;
	char	*pwd;

	buffer = getcwd(NULL, 0);
	if (!buffer)
	{
		if (errno == ENOENT)
		{
			pwd = get_env_value(exec_data, "PWD");
			if (pwd != NULL)
				printf("%s\n", pwd);
			else
			ft_error(exec_data, 
				"minishell: pwd: error retrieving current directory", 1);	
		}
		else
			ft_error(exec_data, "minishell: pwd:", 1);
	}
	else
	{
		printf("%s\n", buffer);
		free(buffer);
	}
	return (1);
}
