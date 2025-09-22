/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:40:42 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/04 23:49:03 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_context	*context_set(t_context	*context, t_data_set operation)
{
	static t_context	*saved_context;

	if (operation == READ)
		return (saved_context);
	if (operation == SET)
		saved_context = context;
	else if (operation == UNSET)
		saved_context = NULL;
	return (saved_context);
}

t_context	*context_read(void)
{
	return (context_set(NULL, READ));
}

t_context	*context_init(char **envp)
{
	t_context	*context;

	context = ft_calloc(1, sizeof(t_context));
	if (context == NULL)
	{
		//TODO: create a error handler function when there is no context 
		exit(EXIT_FAILURE);
	}
	context->env = envp_to_list(envp);
	//TODO: Check failed vs empty env
	if (context->env == NULL)
	{
		//TODO: create a error handler function when there is no context 
		free(context);
		exit(EXIT_FAILURE);
	}
	context->exit_code = 0;
	context->state = PROMPT;
	context->crnt_node = NULL;
	context_set(context, SET);
	return (context);
}
