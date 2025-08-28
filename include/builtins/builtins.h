/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:21:09 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/28 11:15:58 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* ----- LIBRARIES ----- */
# include <stdio.h>
# include "../libft/include/libft.h"
# include "exec/path.h"
# include "exec/multipipes.h"
# include "cd.h"
# include "echo.h"
# include "env.h"
# include "export.h"
# include "pwd.h"
# include "unset.h"
# include "exit.h"

typedef struct s_list	t_env;

int		exec_builtins(t_exec_data *exec_data, int i);
t_list  *envp_to_list(char **envp);
t_var	*create_var(char *env);


#endif