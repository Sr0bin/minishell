/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:45:26 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/02 17:49:55 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_code_read(void)
{
	t_context	*context;

	context = context_read();
	if (context == NULL)
		return (-1);
	return (context->exit_code);
}

int	exit_code_update(int exit_code)
{
	t_context	*context;

	context = context_read();
	if (context == NULL)
		return (1);
	context->exit_code = exit_code;
	return (0);
}
