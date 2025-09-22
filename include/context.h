/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:41:15 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 15:44:41 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H
# include "struct.h"

int			exit_code_read(void);
int			exit_code_update(int exit_code);
t_context	*context_set(t_context	*context, t_data_set operation);
t_context	*context_read(void);
t_context	*context_init(char **envp);
#endif
