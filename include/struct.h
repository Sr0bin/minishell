/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:30:44 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/05 14:41:16 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "libft.h"
# include "parsing/enums.h"
# include "stdbool.h"

typedef struct s_var		t_var;
typedef struct s_token		t_token;
typedef struct s_ast_node	t_ast;
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



typedef struct s_var
{
	char	*key;
	char	*value;
}	t_var;


typedef struct s_ast_node
{
	t_node_type	type;
	t_ast		*left;
	t_ast		*right;
	t_token		*token;
}	t_ast;

typedef struct s_ast_machine
{
	t_token_list	*crnt_tkn_lst;
	t_token			*crnt_tkn;
}	t_ast_machine;

typedef struct s_context
{
	t_list			*env;
	t_shell_state	state;
}	t_context;


typedef void	(*t_handler)(char c, t_parser *p);

#endif
