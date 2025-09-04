/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:23:08 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/04 21:45:36 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

char	*prompt(void)
{
	char		*read;
	t_context	*context;

	context = context_read();
	read = readline("minishell> ");
	if (g_received_signal == SIGINT)
	{
		free(read);
		g_received_signal = 0;
		return (NULL);
	}
	if (read == NULL)
	{
		free(read);
		free_envp(context->env);
		printf("exit\n");
		exit(EXIT_FAILURE);		
	}
	add_history(read);
	return (read);
}

t_ast	*root_generation(char *prompt)
{
	t_list	*token_list;
	t_ast	*node;

	token_list = shell_tokenizer(prompt);
	if (token_list == NULL)
		return (NULL);
	token_list_clean(&token_list);
	//printf("Token Cleaned :\n");
	// print_token_list(token_list);
	node = ast_create(&token_list);
	token_list_destroy(&token_list);
	return (node);
}
