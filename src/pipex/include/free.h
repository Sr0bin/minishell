/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:18:21 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/02 16:12:16 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

void	free_cmd(t_cmds *cmd);
void	free_cmds(t_utils *utils);
void	free_fds(int **fd);
void	free_utils(t_utils *utils);
void	ft_error(t_utils *utils, const char *msg, int exit_code);

#endif
