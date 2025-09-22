/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:22:52 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 13:23:56 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main (int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	t_ast	*node;
	char	*read;
	
	if (isatty(0) != 1)
		return (EXIT_FAILURE);
	context_init(envp);
	setup_signals();
	while (1)
	{
		read = prompt();
		if (read == NULL)
			continue ;
		node = root_generation(read); 
		// print_ast(node);
		exec(node);
		free(read);
	}
}

[[noreturn]] void	exit_minishell(char *prompt)
{
	t_context	*context;

	context = context_read();
	free(prompt);
	free_envp(context->env);
	rl_clear_history();
	free(context);
	printf("exit\n");
	exit(EXIT_SUCCESS);		
}
