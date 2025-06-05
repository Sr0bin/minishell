/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:00:00 by rorollin          #+#    #+#             */
/*   Updated: 2025/06/03 16:45:17 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_H
# define HANDLER_H
# include "struct.h"

void	handle_normal_whitespace(t_parser *p);
void	handle_normal_quote(t_parser *p);
void	handle_normal_operator(t_parser *p);
void	handle_normal_other(t_parser *p);
void	handle_normal_escape(t_parser *p);
void	handle_normal_newline(t_parser *p);
void	handle_normal_eof(t_parser *p);

void	handle_word_whitespace(t_parser *p);
void	handle_word_quote(t_parser *p);
void	handle_word_operator(t_parser *p);
void	handle_word_escape(t_parser *p);
void	handle_word_other(t_parser *p);
void	handle_word_newline(t_parser *p);
void	handle_word_eof(t_parser *p);

void	handle_squote_end(t_parser *p);
void	handle_squote_other(t_parser *p);

void	handle_dquote_end(t_parser *p);
void	handle_dquote_escape(t_parser *p);
void	handle_dquote_other(t_parser *p);

void	handle_op_extend(t_parser *p);
void	handle_op_other(t_parser *p);

t_char_type	char_type(char c);

void	handle_op(t_parser *p);
void	handle_dquote(t_parser *p);
void	handle_squote(t_parser *p);
void	handle_word(t_parser *p);
void	handle_normal(t_parser *p);
#endif
