/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:50:26 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/02 12:22:09 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum s_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}			t_redir_type;

typedef struct s_cmds
{
	char			**cmd;
	char			*path;
	char			*fd_in;
	char			*fd_out;
	t_redir_type	redir_type;
}	t_cmds;

typedef struct s_utils
{
	t_cmds	*cmds;
	int		nb_cmds;
	int		**fd;
	char	**envp;
}	t_utils;

#endif