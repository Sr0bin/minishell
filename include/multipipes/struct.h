/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:17:00 by lserodon          #+#    #+#             */
/*   Updated: 2025/05/30 15:05:16 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef STRUCT_H
# define STRUCT_H
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

typedef struct s_token
{
	t_token_type type;
	const char		*content;
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