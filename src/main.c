/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:22:52 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/20 15:43:29 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main (int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_list	*token_list;
	/*t_redir_list	*redir_list;*/
	t_ast	*node;
	char	*read;

	while (1)
	{
		read = readline("Enter a string to Tokenize :");
		add_history(read);
		token_list = shell_tokenizer(read);
		token_list_clean(&token_list);
		printf("Token Cleaned :\n");
		print_token_list(token_list);
		node = ast_create(&token_list);
		print_ast(node);
		exec(node);
		ast_destroy(&node);
		token_list_destroy(&token_list);
		free(read);
	}
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
