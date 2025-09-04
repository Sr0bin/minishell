/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:29:18 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/04 17:25:11 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE
# include "libft.h"
# include "parsing/parsing.h"
# include "ast_generation/ast.h"
# include "ast_generation/cmd.h"
# include "struct.h"
# include "parsing/token.h"
# include "parsing/handler.h"
# include "debug.h"
# include "parsing/enums.h"
# include "parsing/parsing_struct.h"
# include "signals/signals.h"
# include "exec/exec.h"
# include "exec/ast_to_cmds.h"
# include "builtins/builtins.h"
# include "expand.h"
# include "heredoc.h"
# include "context.h"
# include "prompt.h"
# include <signal.h>

extern volatile	sig_atomic_t	g_received_signal; 

#endif
