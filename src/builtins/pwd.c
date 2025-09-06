/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:57:41 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/06 11:26:34 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"
#include <errno.h>

int	ft_pwd()
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (!buffer)
	{
		ft_error("minishell: pwd: error retrieving current directory", 1);
		return (-1);
	}
	printf("%s\n", buffer);
	free(buffer);
	return (0);
}
