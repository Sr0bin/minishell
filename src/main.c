/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:22:52 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/03 11:27:12 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>


int	main (int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	t_context	*context;
	t_list	*token_list;
	t_ast	*node;
	char	*read;
	t_env	*env;

	context = context_init(envp);
	env = context->env;
	while (1)
	{
		setup_signals();
		read = readline("minishell> ");
		if (g_received_signal == SIGINT)
		{
			free(read);
			g_received_signal = 0;
			continue;
		}
		if (read == NULL)
		{
			free(read);
			free_envp(env);
			printf("exit\n");
			exit (EXIT_FAILURE);		
		}
		add_history(read);
		token_list = shell_tokenizer(read);
		token_list_clean(&token_list);
		//printf("Token Cleaned :\n");
		// print_token_list(token_list);
		node = ast_create(&token_list);
		token_list_destroy(&token_list);
		/*print_ast(node);*/
		exec(node, &token_list, env);
		heredoc_create_fd();
		//ast_destroy(&node);
		free(read);
	}
	free_envp(env);
	free(context); //TODO: clean context destruction
}
