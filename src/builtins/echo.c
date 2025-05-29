/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:20:54 by lserodon          #+#    #+#             */
/*   Updated: 2025/05/27 12:58:28 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		newline(char *str)
{
	int newline;
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while(str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void    ft_echo(int argc, char **argv)
{
	int	i;
	int	j;
	int	no_newline;

	no_newline = 0;
	i = 1;
	while (argv[i] && newline(argv[i]))
	{
		no_newline = 1;
		i++;
	} 
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i < argc - 1)
			printf(" ");
		i++;
	}
	if (no_newline == 0)
		printf("\n");
}

int	main(int argc, char **argv)
{
	ft_echo(argc, argv);
}