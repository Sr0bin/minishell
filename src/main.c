/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:22:52 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/05 08:58:50 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main (int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	t_context	*context;
	t_ast	*node;
	char	*read;

	context = context_init(envp);
	while (1)
	{
		setup_signals();
		read = prompt();
		if (read == NULL)
			continue ;
		node = root_generation(read); 
		/*print_ast(node);*/
		/*heredoc_create_fd();*/
		exec(node);	
		free(read);
	}
	free(context); //TODO: clean context destruction
}
