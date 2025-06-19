/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:49:30 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/17 16:37:56 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

/* int main(int argc, char **argv)
{
    ft_cd(argc, argv);
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("Répertoire courant : %s\n", cwd);
} */