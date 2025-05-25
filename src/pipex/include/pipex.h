/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:08:59 by lserodon          #+#    #+#             */
/*   Updated: 2025/05/24 11:12:29 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* ----- LIBRARIES ----- */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../../libft/include/libft.h"
#include "struct.h"
#include "functions.h"

/* ----- STRUCTURE ----- */

typedef struct s_cmds
{
	char 	**cmd;
	char	*path;
	char	*fd_in;
	char	*fd_out;
}	t_cmds;

typedef struct s_utils
{
	t_cmds	*cmds;
	int		nb_cmds;
	int		**fd;
	char	**envp;
}	t_utils;

#endif