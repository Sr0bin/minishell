/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:50:26 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/19 14:51:29 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "libft.h"

typedef t_list t_redir_list;

/* typedef enum s_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_PIPE,
}			t_redir_type;

typedef struct s_redir
{
	t_redir_type	redir_type;
	char			*fd;
}	t_redir;
 */
typedef struct s_cmds
{
	char			**cmd;
	char			*path;
	t_redir_list	*redir;
}	t_cmds;

typedef struct s_exec_data
{
	t_cmds	*cmds;
	int		nb_cmds;
	int 	**fd;
	char	**envp;
}	t_exec_data;

#endif