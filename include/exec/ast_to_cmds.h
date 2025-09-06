/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_cmds.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:53:51 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/06 15:13:07 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_TO_CMDS_H
# define AST_TO_CMDS_H

# include "struct.h"
# include "structs.h"

/* ----- AST_TO_CMDS.C ----- */

t_list	*fill_redir(t_exec_data *exec_data, t_cmd cmd);
void	ast_to_cmds(t_exec_data *exec_data, t_ast *root);
void	fill_one_cmd(t_exec_data *exec_data, t_cmd cmd, int *i);
void	fill_cmds(t_exec_data *exec_data, t_ast *node, int *i);
void	init_exec_data(t_exec_data *exec_data, t_ast *root);


/* ----- AST_UTILS.C ----- */

int		count_commands(t_ast *node);
int		count_nbr_args(char **args);

#endif