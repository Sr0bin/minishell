/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:01:09 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/08 13:12:47 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H
# include "struct.h"

t_redir	*create_redir(t_redir_type type, char *filename);
void	*free_redir(t_redir **redir);
t_cmd	*create_cmd(t_redir_list *redir, char *path, char **args, char **envp);
void	*free_cmd(t_cmd **cmd);
#endif

