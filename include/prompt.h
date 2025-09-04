/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:24:09 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/04 18:10:18 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H
# define PROMPT_NORMAL "minishell> "
# define PROMPT_HEREDOC "minishell> "
# include "struct.h"

char	*prompt(void);
t_ast	*root_generation(char *str);
#endif

