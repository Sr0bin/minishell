/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:32:03 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/23 13:33:10 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes/multipipes.h"

int main(int argc, char **argv, char **envp)
{
	 (void)argc;
	 (void)argv;
	t_token tok_grep = {TOKEN_WORD, "ls", NULL, NULL};
	t_token tok_dotc = {TOKEN_WORD, "-l", NULL, NULL};
	tok_grep.next = &tok_dotc;
	tok_dotc.prev = &tok_grep;

	t_ast_node cmd_grep = {
    	.type = NODE_COMMAND,
    	.left = NULL,
    	.right = NULL,
    	.token_list = &tok_grep
	};
	exec(&cmd_grep, envp);
}
