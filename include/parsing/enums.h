/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:10:50 by rorollin          #+#    #+#             */
/*   Updated: 2025/07/29 18:12:57 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef enum e_char_type
{
	CHAR_ERROR = -1,
	CHAR_WHITESPACE,
	CHAR_SQUOTE,
	CHAR_DQUOTE,
	CHAR_OPERATOR,
	CHAR_NEWLINE,
	CHAR_ESCAPE,
	CHAR_EOF,
	CHAR_OTHER,
}	t_char_type;

typedef enum e_parse_state
{
	STATE_NORMAL,
	STATE_SQUOTE,
	STATE_DQUOTE,
	STATE_OP,
}	t_ps_state;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_OPERATOR,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_OR_IF,
	TOKEN_AND_IF,
	TOKEN_IO_NUMBER,
	TOKEN_NEWLINE,
	TOKEN_EOF,
}	t_token_type;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_APPEND,
	NODE_ERROR,
}	t_node_type;

#endif

