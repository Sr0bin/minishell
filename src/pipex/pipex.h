/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:08:59 by lserodon          #+#    #+#             */
/*   Updated: 2025/05/13 13:38:46 by lserodon         ###   ########.fr       */
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
	int 	fd[2];
	char	**cmd1;
	char	**cmd2;
	char	*path_cmd1;
	char	*path_cmd2;
} t_utils;

/* ----- FUNCTIONS ------ */

char	*find_path(char **envp, char *cmd);
char	*split_word(char const *s, char c);
char 	**parse_cmd(char *cmd);
void	free_array(char **array);
void    exec_cmd1(t_utils *utils, char **envp);
void    exec_cmd2(t_utils *utils, char **envp);
void	inits_utils(char **argv, char **envp, t_utils *utils);
void	exec_pipex(t_utils *utils, char **envp);
void	close_files(t_utils *utils);

#endif