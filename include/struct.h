/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:30:44 by rorollin          #+#    #+#             */
/*   Updated: 2025/05/26 16:19:34 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "libft.h"

typedef struct s_token t_token;
typedef struct s_ast_node t_ast_node;


typedef	enum	e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,				// |
	TOKEN_REDIR_IN,			// <
	TOKEN_REDIR_OUT,		// >
	TOKEN_REDIR_APPEND,		// >>
	TOKEN_HEREDOC,			// <<
	TOKEN_OR_IF,			// ||
	TOKEN_AND_IF,			// &&
	TOKEN_IO_NUMBER,		// 2>
	TOKEN_NEWLINE,			// \n
	TOKEN_EOF,				// ctrl-d
} t_token_type;

typedef t_list t_token_list;

typedef struct s_token
{
	char		*content;
	t_token_type type;
	t_token 	*next;
	t_token 	*prev;
}	t_token;

typedef enum e_state
{
	STATE_DEFAULT,
	STATE_WORD,
	STATE_SQUOTE,
	STATE_DQUOTE,
	STATE_OPERATOR,
}	t_state;

typedef	enum	e_char_type
{
	CHAR_WHITESPACE,
	CHAR_QUOTE_SINGLE,
	CHAR_QUOTE_DOUBLE,
	CHAR_LESS,
	CHAR_GREATER,
	CHAR_PIPE,
	CHAR_AMPERSAND,
	CHAR_SEMICOLON,
	CHAR_NEWLINE,
	CHAR_ESCAPE,
	CHAR_OTHER,
	CHAR_EOF,
}	t_char_type;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_APPEND,
} t_node_type;

typedef struct s_ast_node
{
	t_node_type	type;
	t_ast_node	*left;
	t_ast_node	*right;
	t_token		*token_list;
} t_ast_node;
#endif
