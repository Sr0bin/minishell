/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:20:54 by lserodon          #+#    #+#             */
/*   Updated: 2025/05/15 18:00:18 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void    ft_echo(int argc, char **argv)
{
	int	i;

	i = 1;
	while (ft_strncmp(argv[i], "-n", ft_strlen(argv[i])) == 0)
		i++;
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i < argc - 1)
			printf(" ");
		i++;   
	}
	if (ft_strncmp(argv[1], "-n", ft_strlen(argv[1])) != 0)
		printf("\n");
}

int main(int argc, char **argv)
{
    ft_echo(argc, argv);
}