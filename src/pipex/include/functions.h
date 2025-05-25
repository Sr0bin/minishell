/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:02:07 by lserodon          #+#    #+#             */
/*   Updated: 2025/05/24 15:22:32 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

#include "pipex.h"

typedef struct s_utils t_utils;

char	*find_path(char **envp, char *cmd);
void	free_array(char **array);
void	exec_pipex(t_utils *utils);
void	close_all_fds(t_utils *utils);

/* ----- PIPES.C ----- */
void	init_utils(t_utils *utils, t_ast_node *root);
void	init_pipes(t_utils *utils);
//char	***ast_to_cmds(t_ast_node *root);
int		count_commands(t_ast_node *node);
void 	free_cmds(char ***cmds);
void	print_cmds(t_utils *utils);
//void	fill_cmds(t_ast_node *node, char ***cmds, int *i);
int		count_nbr_token(t_token *token);
void	token_to_argv(t_token *token, char ***cmds, int *i);
int		is_next_of_redir(t_token *token);
int		count_nbr_args(t_token *token);
void	fill_one_cmd(t_utils *utils, t_token *token, int *i);
void	fill_cmds(t_utils *utils, t_ast_node *node, int *i);
void	ast_to_cmds(t_utils *utils, t_ast_node *root);
void	exec_multipipe(t_ast_node *root, char **envp);
/* ----- EXEC.C ----- */

void    exec_cmd(t_utils *utils, int i);
t_ast_node *make_simple_ast(void);
void	exec_pipex(t_utils *utils);
void	init_pipes(t_utils *utils);
void	ast_to_cmds(t_utils *utils, t_ast_node *root);
void	init_utils(t_utils *utils, t_ast_node *root);

#endif