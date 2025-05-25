/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:32:03 by lserodon          #+#    #+#             */
/*   Updated: 2025/05/25 10:04:20 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

// --- TOKENS ---

// Redirection in
t_token redir_in     = {TOKEN_REDIR_IN, "<", NULL, NULL};
t_token infile       = {TOKEN_WORD, "input.txt", NULL, &redir_in};
redir_in.next = &infile;

// grep hello
t_token grep_tok     = {TOKEN_WORD, "grep", NULL, &infile};
infile.next = &grep_tok;
t_token hello_tok    = {TOKEN_WORD, "hello", NULL, &grep_tok};
grep_tok.next = &hello_tok;

// sort
t_token sort_tok     = {TOKEN_WORD, "sort", NULL, NULL};

// wc -l + redir out
t_token wc_tok       = {TOKEN_WORD, "wc", NULL, NULL};
t_token dash_l_tok   = {TOKEN_WORD, "-l", NULL, &wc_tok};
wc_tok.next = &dash_l_tok;
t_token redir_out    = {TOKEN_REDIR_OUT, ">", NULL, &dash_l_tok};
dash_l_tok.next = &redir_out;
t_token outfile      = {TOKEN_WORD, "output.txt", NULL, &redir_out};
redir_out.next = &outfile;

// --- AST NODES ---

// grep hello + < input.txt
t_ast_node node_cmd1 = {
	NODE_COMMAND,
	NULL,
	NULL,
	&redir_in
};

// sort
t_ast_node node_cmd2 = {
	NODE_COMMAND,
	NULL,
	NULL,
	&sort_tok
};

// wc -l > output.txt
t_ast_node node_cmd3 = {
	NODE_COMMAND,
	NULL,
	NULL,
	&wc_tok
};

// Pipe 1: grep hello < input.txt | sort
t_ast_node pipe1 = {
	NODE_PIPE,
	&node_cmd1,
	&node_cmd2,
	NULL
};

// Pipe 2: (grep hello | sort) | wc -l > output.txt
t_ast_node root = {
	NODE_PIPE,
	&pipe1,
	&node_cmd3,
	NULL
};

	exec_multipipe(&root, envp);
}
