/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:31:46 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/17 16:22:41 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>

#include <stdlib.h>

int	main(void)
{
	t_env	*env = NULL;
	char	*args1[] = {"USER=lulussi", "SHELL=/bin/bash", "PATH", NULL};
	char	*args2[] = {"EDITOR=vim", "USER=root", NULL};

	printf(">>> Export avec args1 :\n");
	ft_export(&env, args1);

	printf("\n>>> Export avec args2 (remplace USER, ajoute EDITOR) :\n");
	ft_export(&env, args2);

	printf("\n>>> Export sans arguments (affichage trié) :\n");
	ft_export(&env, NULL);

	return (0);
}
