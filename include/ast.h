/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:48:47 by rorollin          #+#    #+#             */
/*   Updated: 2025/07/31 19:02:47 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "struct.h"
t_ast	*generate_full_ast(t_token_list **list);
t_ast	*generate_simple_command(t_ast_machine *mchn);
t_ast	*generate_redir_node(t_ast_machine *mchn);
t_ast	*generate_pipe_node(t_ast_machine *mchn);
t_ast	*generate_node(t_node_type type, t_token *token);
t_ast_machine	*create_ast_machine(t_token_list *input_list);
t_ast_machine	*advance_token(t_ast_machine *mchn);
void	*free_ast(t_ast **node);
void	*free_ast_machine(t_ast_machine **machine);
void	*free_node(t_ast **node);
t_node_type token_to_node_type(t_token_type type);
void	*free_token_only_list(t_token_list **t_list);
int	token_type_redir(t_token *token);
t_token_list	*find_first_redir(t_token_list *list);
t_token_list	*find_first_pipe(t_token_list *list);
#endif

