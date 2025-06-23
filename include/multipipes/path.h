/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:32:19 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/20 11:06:34 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

char	*find_path(t_utils *utils);
char	*get_env_path(t_utils *utils, char **envp);
void	free_array(char **array);

#endif