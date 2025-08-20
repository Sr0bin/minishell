/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:08:38 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/20 15:53:29 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_STRUCT_H
# define PARSING_STRUCT_H

# include "enums.h"
# include "libft.h"

typedef struct s_var		t_var;
typedef struct s_token		t_token;
typedef struct s_ast		t_ast;
typedef struct s_parser		t_parser;
typedef struct s_transition	t_transition;

typedef t_list				t_env;
typedef t_list				t_token_list;
typedef t_list				t_transition_list;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	t_token			*next;
	t_token			*prev;
}	t_token;

typedef struct s_parser
{
	t_ps_state		state;
	char			*input;
	char			*crnt_pos;
	char			*start_pos;
	t_token			*crnt_token;
	t_list			*token_list;
}	t_parser;
#endif
