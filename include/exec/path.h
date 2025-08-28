/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:32:19 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/28 11:16:13 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

#include "structs.h"

char	*find_path(t_exec_data *utils, int i);
char	*get_env_value(t_exec_data *exec_data, char *key);
char	*get_env_path(t_exec_data *exec_data);
void	free_array(char **array);

#endif