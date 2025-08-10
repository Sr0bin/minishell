/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:48:47 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/10 17:47:05 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "struct.h"
t_ast	*ast_create(t_token_list **list);
t_redir	*create_redir_token(t_token_list *tkn_lst);
void	*redir_destroy(t_redir_list **redir_list, t_redir **redir);
t_cmd	cmd_create(t_token_list *tkn_lst);
t_ast	*node_cmd_create(t_token_list *tkn_lst);
t_ast	*node_pipe_create(t_token_list *tkn_lst, t_token_list *last_pipe);
t_ast	*generate_node(t_node_type type, t_cmd cmd);
t_ast_machine	*create_ast_machine(t_token_list *input_list);
t_ast_machine	*advance_token(t_ast_machine *mchn);
/*void	*free_ast(t_ast **node);*/
void	*free_ast_machine(t_ast_machine **machine);
void	*free_node(t_ast **node);
t_node_type token_to_node_type(t_token_type type);
void	*free_token_only_list(t_token_list **t_list);
int	token_type_redir(t_token *token);
t_token_list	*redir_find_first(t_token_list *list);
t_token_list	*pipe_find_first(t_token_list *list);
t_token_list	*pipe_find_n(t_token_list *list, int count);
t_token_list	*pipe_find_last(t_token_list *list);
int	pipe_count(t_token_list	*tkn_lst, t_token_list *last);
#endif

