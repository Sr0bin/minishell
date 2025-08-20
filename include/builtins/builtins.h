/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:21:09 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/20 11:19:03 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* ----- LIBRARIES ----- */
# include <stdio.h>
# include "../libft/include/libft.h"
# include "multipipes/structs.h"
# include "multipipes/ast_to_cmds.h"
# include "cd.h"
# include "echo.h"
# include "env.h"
# include "export.h"
# include "pwd.h"
# include "unset.h"

typedef struct s_list	t_env;

#endif