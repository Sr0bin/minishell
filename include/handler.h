/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:00:00 by rorollin          #+#    #+#             */
/*   Updated: 2025/05/28 16:23:28 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_H
# define HANDLER_H
# include "struct.h"

void	handle_normal_whitespace(char c, t_parser *p);
void	handle_normal_quote(char c, t_parser *p);
void	handle_normal_dquote(char c, t_parser *p);
void	handle_normal_operator(char c, t_parser *p);
void	handle_normal_other(char c, t_parser *p);
void	handle_normal_escape(char c, t_parser *p);
void	handle_normal_newline(char c, t_parser *p);
void	handle_normal_eof(char c, t_parser *p);

void	handle_word_whitespace(char c, t_parser *p);
void	handle_word_squote(char c, t_parser *p);
void	handle_word_dquote(char c, t_parser *p);
void	handle_word_operator(char c, t_parser *p);
void	handle_word_escape(char c, t_parser *p);
void	handle_word_other(char c, t_parser *p);
void	handle_word_newline(char c, t_parser *p);
void	handle_word_eof(char c, t_parser *p);

void	handle_squote_end(char c, t_parser *p);
void	handle_squote_other(char c, t_parser *p);

void	handle_dquote_end(char c, t_parser *p);
void	handle_dquote_escape(char c, t_parser *p);
void	handle_dquote_other(char c, t_parser *p);

void	handle_op_extend(char c, t_parser *p);
void	handle_op_other(char c, t_parser *p);
#endif
