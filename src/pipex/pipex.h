/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:08:59 by lserodon          #+#    #+#             */
/*   Updated: 2025/05/21 15:30:46 by lserodon         ###   ########.fr       */
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
char	***ast_to_cmds(t_ast_node *root);
int		count_commands(t_ast_node *node);
void 	free_cmds(char ***cmds);
void	print_cmds(char ***cmds);
void	fill_cmds(t_ast_node *node, char ***cmds, int *i);
int		count_nbr_token(t_token *token);
void	token_to_argv(t_token *token, char ***cmds, int *i);
/* ----- EXEC.C ----- */

void	exec_first_cmd(t_utils *utils);
void	exec_mid_cmd(t_utils *utils, int i);
void	exec_last_cmd(t_utils *utils, int i);

#endif