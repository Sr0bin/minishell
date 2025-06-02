/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:32:03 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/02 12:16:58 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/multipipes.h"

int main(int argc, char **argv, char **envp)
{
	 (void)argc;
	(void)argv;
	// Fichiers
t_token token_infile = {TOKEN_WORD, "infile.txt", NULL, NULL};
t_token token_outfile = {TOKEN_WORD, "output.txt", NULL, NULL};

// Commandes
t_token token_grep1 = {TOKEN_WORD, "grep", NULL, NULL};
t_token token_grep2 = {TOKEN_WORD, "hello", NULL, &token_grep1};
token_grep1.next = &token_grep2;

t_token token_sort = {TOKEN_WORD, "sort", NULL, NULL};

t_token token_wc1 = {TOKEN_WORD, "wc", NULL, NULL};
t_token token_wc2 = {TOKEN_WORD, "-l", NULL, &token_wc1};
token_wc1.next = &token_wc2;

// CMD nodes
t_ast_node cmd_grep = {NODE_COMMAND, NULL, NULL, &token_grep1};
t_ast_node cmd_sort = {NODE_COMMAND, NULL, NULL, &token_sort};
t_ast_node cmd_wc = {NODE_COMMAND, NULL, NULL, &token_wc1};

// FILE nodes (sous forme de commande simple contenant le token fichier)
t_ast_node file_in = {NODE_COMMAND, NULL, NULL, &token_infile};
t_ast_node file_out = {NODE_COMMAND, NULL, NULL, &token_outfile};

// REDIR_IN : < input.txt grep hello
t_ast_node redir_in = {NODE_REDIR_IN, &cmd_grep, &file_in, NULL};

// PIPE gauche : (grep < input.txt) | sort
t_ast_node pipe1 = {NODE_PIPE, &redir_in, &cmd_sort, NULL};

// REDIR_OUT : wc -l > output.txt
t_ast_node redir_out = {NODE_REDIR_APPEND, &cmd_wc, &file_out, NULL};

// PIPE racine : (pipe1) | (wc -l > output.txt)
t_ast_node pipe2 = {NODE_PIPE, &pipe1, &redir_out, NULL};

//  AST final
t_ast_node *ast_root = &pipe2;

	exec_multipipes(ast_root, envp);
}
