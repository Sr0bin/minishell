/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:30:03 by rorollin          #+#    #+#             */
/*   Updated: 2025/06/27 21:08:05 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PARSING_H
# define PARSING_H
# include "struct.h"

t_token	*generate_token(t_parser *parser, t_token_type type);
t_token_list	*shell_tokenizer(char *input);
t_token_list	*generate_token_list(t_parser *parser);
void	*update_parser_token(t_parser *parser);
void	advance_parser(t_parser	*parser);
t_parser	*parser_init(char *input);
int	parser_stop(t_parser *p);
void	remove_char(char *text);
t_char_type	safe_char_type(t_parser *p, int offset);
#endif
