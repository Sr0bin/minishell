/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:49:30 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/20 11:19:34 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

void	ft_cd(int argc, char **argv)
{
	char	*path;

	if (argc == 2)
	{
		path = getenv("HOME");
		if (!path || chdir(path) == -1)
			perror("minishell: cd");
	}
	else
	{
		path = argv[2];
		if (chdir(path) == -1)
			perror("minishell: cd");
	}
}
