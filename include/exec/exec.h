/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:07:32 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/29 11:49:11 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"

int		exec_single_cmd(t_exec_data *exec_data, int i);
void	close_parent_fds(t_exec_data *utils, int i);
int		exec_cmd(t_exec_data *utils, int i);
int		exec_pipex(t_exec_data *utils);


#endif