/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:29:18 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/26 16:58:16 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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
# include "exec/multipipes.h"
# include "signals/signals.h"
# include <signal.h>

extern volatile	sig_atomic_t	g_received_signal; 

#endif
