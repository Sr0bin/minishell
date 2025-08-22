/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:50:26 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/22 13:56:03 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "libft.h"

typedef t_list t_redir_list;

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
	int		status;
}	t_exec_data;

#endif