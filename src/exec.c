/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:13:39 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/17 10:51:22 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/exec.h"

void	exec_fork(t_cmd *cmd)
{
	int	fd_in;
	int fd_out;

	fd_in = set_input_fd(cmd);
	fd_out = set_output_fd(cmd);
	if (fd_in > 2 && close(fd_in) == -1)
		perror("minishell: close input fd");
	if (fd_out > 2 && close(fd_out) == -1)
		perror("minishell: close output fd");
	cmd->path = find_path(cmd);
	if (!cmd->path)
		ft_error(cmd, "minishell: command not found", 127);
	if (execve(cmd->path, cmd->cmd, cmd->envp) == -1)
		ft_error(cmd, "minishell: execve failed", 1);
}

void	exec_cmd(t_cmd *cmd)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		ft_error(cmd, "minishell: fork failed", 1);
	else if (pid == 0)
		exec_fork(cmd);
	while (wait(NULL) > 0)
		;
	free_utils(cmd);
	exit (0);
}


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	// Allocation tokens commande : "ls" et "-l"
	t_token *tok_ls = malloc(sizeof(t_token));
	tok_ls->type = TOKEN_WORD;
	tok_ls->content = "ls";
	tok_ls->prev = NULL;

	t_token *tok_l = malloc(sizeof(t_token));
	tok_l->type = TOKEN_WORD;
	tok_l->content = "-l";
	tok_l->prev = tok_ls;
	tok_ls->next = tok_l;
	tok_l->next = NULL;

	// Noeud commande
	t_ast_node *cmd_node = malloc(sizeof(t_ast_node));
	cmd_node->type = NODE_COMMAND;
	cmd_node->token_list = tok_ls;
	cmd_node->left = NULL;
	cmd_node->right = NULL;

	// Token fichier de sortie
	t_token *tok_outfile = malloc(sizeof(t_token));
	tok_outfile->type = TOKEN_WORD;
	tok_outfile->content = "outfile.txt";
	tok_outfile->prev = NULL;
	tok_outfile->next = NULL;

	// Noeud fichier sortie
	t_ast_node *outfile_node = malloc(sizeof(t_ast_node));
	outfile_node->type = NODE_COMMAND; // même type que commande simple
	outfile_node->token_list = tok_outfile;
	outfile_node->left = NULL;
	outfile_node->right = NULL;

	// Noeud redirection sortie
	t_ast_node *redir_out_node = malloc(sizeof(t_ast_node));
	redir_out_node->type = NODE_REDIR_OUT;
	redir_out_node->left = cmd_node;
	redir_out_node->right = outfile_node;
	redir_out_node->token_list = NULL;

	// Test d'affichage
	printf("Commande: %s %s\n", cmd_node->token_list->content, cmd_node->token_list->next->content);
	printf("Redirection > vers: %s\n", redir_out_node->right->token_list->content);

	// Ici, tu peux ajouter ta fonction fill_redir en passant redir_out_node

	// Pas de free pour éviter surcharge dans l'exemple minimal

	exec_single_cmd(redir_out_node, envp);
}