/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:30:44 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/31 22:22:01 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "../libft/include/libft.h"
# include "parsing/enums.h"
# include "stdbool.h"

typedef struct s_var		t_var;
typedef struct s_token		t_token;
typedef struct s_ast		t_ast;
typedef struct s_parser		t_parser;
typedef struct s_transition	t_transition;
typedef struct s_cmd		t_cmd;

typedef t_list				t_env;
typedef t_list				t_token_list;
typedef t_list				t_transition_list;

typedef struct s_redir		t_redir;
typedef t_list				t_redir_list;

typedef enum e_shell_state
{
	INIT,
	PROMPT,
	INPUT,
	HEREDOC,
}	t_shell_state;

typedef struct s_var
{
	char	*key;
	char	*value;
}	t_var;

typedef struct s_cmd
{
	t_redir_list	*redir;
	char			**args;
}	t_cmd;

typedef struct s_ast
{
	t_node_type	type;
	union
	{
		t_cmd	cmd;
		struct
		{
			t_ast	*left;
			t_ast	*right;
		} s_pipe;
	};
}	t_ast;

typedef struct s_ast_machine
{
	t_token_list	*crnt_tkn_lst;
	t_token			*crnt_tkn;
}	t_ast_machine;

typedef enum s_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_PIPE,
}			t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	union
	{
		char			*filename;
		struct
		{
			int				read;
			int				write;
		} s_heredoc;

	};
}	t_redir;

typedef struct s_context
{
	t_env			*env;
	int				exit_code;
	t_shell_state	state;
	t_ast			*crnt_node;
}	t_context;

typedef	enum	e_data_set
{
	SET,
	UNSET,
	READ
}	t_data_set;
typedef void				(*t_handler)(char c, t_parser *p);

typedef enum s_exec_data_context {
	SET_EXEC_DATA,
	READ_EXEC_DATA,
	UNSET_EXEC_DATA
} t_exec_data_context;

#endif
