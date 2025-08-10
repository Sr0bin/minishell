/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:22:52 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/10 17:54:57 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
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
		clean_token_list(&token_list);
		printf("Token Cleaned :\n");
		print_token_list(token_list);
		node = ast_create(&token_list);
		print_ast(node);
		/*redir_list = redir_list_create(token_list);*/
		/*print_redir_list(redir_list);*/
		/*ft_lstclear(&redir_list, (void(*))free_redir);*/
		free_token_list(&token_list);
		free(read);
	}
}
