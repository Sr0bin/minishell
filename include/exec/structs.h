/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:50:26 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/16 08:09:02 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libft.h"
# include "ast_generation/ast.h"
# include "parsing/token.h"

typedef t_list	t_redir_list;

typedef struct s_cmds
{
	char			**cmd;
	char			*path;
	t_redir_list	*redir;
}	t_cmds;

typedef struct s_exec_data
{
	int					exit_code;
	int					nb_cmds;
	int					*pids;
	int					**fd;
	t_cmds				*cmds;
	t_list				*envp;
	t_ast				*root;
}	t_exec_data;

#endif
