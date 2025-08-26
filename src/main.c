/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:22:52 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/26 17:21:52 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main (int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	t_list	*token_list;
	/*t_redir_list	*redir_list;*/
	t_ast	*node;
	char	*read;
	t_env	*env;
	
	env = envp_to_list(envp);
	while (1)
	{
		setup_signals();
		read = readline("minishell> ");
		if (g_received_signal == SIGINT)
		{
			free(read);
			g_received_signal = 0;
			//mettre code erreur 
			continue;
		}
		if (read == NULL)
		{
			free(read);
			free_envp(env);
			printf("exit\n");
			exit (1);		
		}
		add_history(read);
		token_list = shell_tokenizer(read);
		token_list_clean(&token_list);
		//printf("Token Cleaned :\n");
		//print_token_list(token_list);
		node = ast_create(&token_list);
		//print_ast(node);
		exec(node, &token_list, env);
		//ast_destroy(&node);
		//token_list_destroy(&token_list);
		free(read);
	}
	free_envp(env);
}


/*int	main (int argc, char **argv)*/
/*{*/
/*	(void) argc;*/
/*	(void) argv;*/
/*	t_list	*token_list;*/
	/*t_redir_list	*redir_list;*/
/*	t_ast	*node;*/
/*	char	*read;*/
/**/
/*	while (1)*/
/*	{*/
/*		read = readline("Enter a string to Tokenize :");*/
/*		add_history(read);*/
/*		token_list = shell_tokenizer(read);*/
/*		token_list_clean(&token_list);*/
/*		printf("Token Cleaned :\n");*/
/*		print_token_list(token_list);*/
/*		node = ast_create(&token_list);*/
/*		print_ast(node);*/
		/*print_token_list(token_list_skip_redir(token_list));*/
		/*printf("Args count : %zu\n", args_cmd_count(token_list));*/
		/*exec(node);*/
/*		ast_destroy(&node);*/
/*		token_list_destroy(&token_list);*/
/*		free(read);*/
/*	}*/
/*}*/
