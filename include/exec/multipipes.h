/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:08:59 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/27 13:38:37 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTIPIPES_H
# define MULTIPIPES_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include "ast_to_cmds.h"
# include "exec_multipipes.h"
# include "exec.h"
# include "free.h"
# include "path.h"
# include "pipes.h"
# include "structs.h"
# include "env_to_array.h"
# include "builtins/builtins.h"
# include "../../libft/include/libft.h"
# include "ast_generation/ast.h"
# include "parsing/token.h"
# include "signals/signals.h"

#endif