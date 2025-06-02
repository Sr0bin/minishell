/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:07:32 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/02 12:21:46 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"

int		set_input_fd(t_utils *utils, int i);
int		set_output_fd(t_utils *utils, int i);
void	close_parent_fds(t_utils *utils, int i);
void	exec_cmd(t_utils *utils, int i);
void	exec_multipipes(t_ast_node *root, char **envp);
void	exec_pipex(t_utils *utils);

#endif