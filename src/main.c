/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:22:52 by rorollin          #+#    #+#             */
/*   Updated: 2025/07/30 19:42:17 by rorollin         ###   ########.fr       */
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
	char	*read;

	while (1)
	{
		read = readline("Enter a string to Tokenize :");
		add_history(read);
		token_list = shell_tokenizer(read);
		/*print_token_list(token_list);*/
		clean_token_list(&token_list);
		printf("Token Cleaned :\n");
		print_token_list(token_list);
		generate_full_ast(&token_list);
		free_token_list(&token_list);
		free(read);
	}
}
