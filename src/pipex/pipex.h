/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:08:59 by lserodon          #+#    #+#             */
/*   Updated: 2025/05/17 10:55:01 by lserodon         ###   ########.fr       */
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

/* ----- STRUCTURE ----- */

typedef struct s_utils
{
	int		infile;
	int		outfile;
	char	**envp;
	int		**fd;
	int		nb_commands;
	char	**cmds;
	char	*path;
	pid_t	*forks;
} t_utils;

/* ----- PIPEX.C ------ */

char	*find_path(char **envp, char *cmd);
void	free_array(char **array);
void	exec_pipex(t_utils *utils);
void	close_fds(t_utils *utils);

/* ----- PIPES.C ----- */

void	init_pipes(t_utils *utils);

/* ----- EXEC.C ----- */

void	exec_first_cmd(t_utils *utils);
void	exec_mid_cmd(t_utils *utils, int i);
void	exec_last_cmd(t_utils *utils, int i);

#endif