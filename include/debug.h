/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:32:23 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/05 14:43:54 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H
# include "struct.h"
void	print_token(t_token token);
void	print_token_list(t_token_list *list);
void	print_parser_state(t_parser *parser);
void	print_ast(t_ast *root);
void print_ast_state(t_ast_machine *mchn, const char *location);
#endif

