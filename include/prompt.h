/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:24:09 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 15:43:09 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H
# define PROMPT_NORMAL "minishell> "
# define PROMPT_HEREDOC "> "
# include "struct.h"

char	*prompt(void);
void	*prompt_heredoc(int w_fd, char *eof);
t_ast	*root_generation(char *prompt);
#endif
