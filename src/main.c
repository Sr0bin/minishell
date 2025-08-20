/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:22:52 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/20 13:18:27 by lserodon         ###   ########.fr       */
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
		free_ast(&node);
		token_list_destroy(&token_list);
		free(read);
	}
}
