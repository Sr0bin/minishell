/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:07:32 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/22 13:56:13 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"

void	close_parent_fds(t_exec_data *utils, int i);
void	exec_cmd(t_exec_data *utils, int i);
void	exec_multipipes(t_ast *root, char **envp);
void	exec_pipex(t_exec_data *utils);

#endif