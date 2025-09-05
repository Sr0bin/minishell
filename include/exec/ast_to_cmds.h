/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_cmds.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:53:51 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/05 09:38:18 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_TO_CMDS_H
# define AST_TO_CMDS_H

# include "struct.h"
# include "structs.h"

/* ----- AST_TO_CMDS.C ----- */

int		init_exec_data(t_exec_data *exec_data, t_ast *root);
t_list	*fill_redir(t_cmd cmd);
int		fill_one_cmd(t_exec_data *exec_data, t_cmd cmd, int *i);
int		fill_cmds(t_exec_data *exec_data, t_ast *node, int *i);
int		ast_to_cmds(t_exec_data *exec_data, t_ast *root);


/* ----- AST_UTILS.C ----- */

int		count_commands(t_ast *node);
int		count_nbr_args(char **args);

#endif