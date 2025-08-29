/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:18:21 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/28 20:24:25 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

void	free_cmd(t_cmds *cmd);
void	free_cmds(t_exec_data *utils);
void	free_envp(t_env	*env);
void	free_fds(int **fd, int nb_cmd);
void	free_exec_data(t_exec_data *utils);
void	ft_error(t_exec_data *utils, const char *msg, int exit_code);
void	ft_fatal_error(t_exec_data *exec_data, const char *msg, int exit_code);

#endif
