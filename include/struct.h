/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:30:44 by rorollin          #+#    #+#             */
/*   Updated: 2025/05/28 16:26:01 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "libft.h"
# include "stdbool.h"

typedef struct s_var		t_var;
typedef struct s_token		t_token;
typedef struct s_ast_node	t_ast_node;
typedef struct s_parser		t_parser;
typedef struct s_transition	t_transition;

typedef t_list				t_env;
typedef t_list				t_token_list;
typedef t_list				t_transition_list;

typedef enum e_shell_state
{
	INIT,
	PROMPT,
	INPUT,
	HEREDOC,
}	t_shell_state;

typedef enum e_char_type
{
	CHAR_WHITESPACE,
	CHAR_QUOTE,
	CHAR_OPERATOR,
	CHAR_NEWLINE,
	CHAR_ESCAPE,
	CHAR_EOF,
	CHAR_OTHER,
}	t_char_type;
# define CHAR_COUNT 7

typedef enum e_token_type
{
	TOKEN_WORD,
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
# define TOKEN_COUNT 11

typedef enum e_parse_state
{
	STATE_NORMAL,
	STATE_SQUOTE,
	STATE_DQUOTE,
}	t_ps_state;
# define STATE_COUNT 3

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_APPEND,
}	t_node_type;

typedef struct s_var
{
	char	*key;
	char	*value;
}	t_var;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	t_token			*next;
	t_token			*prev;
}	t_token;

typedef struct s_ast_node
{
	t_node_type	type;
	t_ast_node	*left;
	t_ast_node	*right;
	t_token		*token_list;
}	t_ast_node;

typedef struct s_context
{
	t_list			*env;
	t_shell_state	state;
}	t_context;

typedef struct s_parser
{
	t_ps_state		state;
	char			*input;
	char			*pos;
	t_list			*token_list;
}	t_parser;

typedef void	(*t_handler)(char c, t_parser *p);

#endif
