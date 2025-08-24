/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:50:26 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/23 09:41:47 by lserodon         ###   ########.fr       */
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
	int		nb_cmds;
	int 	**fd;
	int		status;
	t_cmds	*cmds;
	t_list	*envp;
}	t_exec_data;

#endif