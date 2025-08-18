/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_cmds.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:53:51 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/02 12:07:01 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_TO_CMDS_H
# define AST_TO_CMDS_H

# include "struct.h"
# include "structs.h"

int		count_commands(t_ast_node *node);
int		count_nbr_args(t_token *token);
void	ast_to_cmds(t_utils *utils, t_ast_node *root);
void	fill_one_cmd(t_utils *utils, t_token *token, int *i);
void	fill_cmds(t_utils *utils, t_ast_node *node, int *i);
void	fill_redir(t_utils *utils, t_node_type redir_type, t_ast_node *node,
			int *i);
void	init_utils(t_utils *utils, t_ast_node *root);

#endif