/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:23:08 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 13:24:33 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

char	*prompt(void)
{
	char		*read;

	read = readline("minishell> ");
	if (g_received_signal == SIGINT)
	{
		free(read);
		g_received_signal = 0;
		return (NULL);
	}
	if (read == NULL)
		exit_minishell(read);
	add_history(read);
	return (read);
}

void	*prompt_heredoc(int w_fd, char *eof)
{
	char	*prompt;

	while (1)
	{
		prompt = readline(PROMPT_HEREDOC);
		if (prompt == NULL || ft_strcmp(eof, prompt) == 0)
			break ;
		write(w_fd, prompt, ft_strlen(prompt));
		write(w_fd, "\n", 1);
		free(prompt);
	}
	free(prompt);
	return (NULL);
}

t_ast	*root_generation(char *prompt)
{
	t_list	*token_list;
	t_ast	*node;

	token_list = shell_tokenizer(prompt);
	if (token_list == NULL)
		return (NULL);
	token_list_clean(&token_list);
	node = ast_create(&token_list);
	token_list_destroy(&token_list);
	return (node);
}
