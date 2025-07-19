/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:22:49 by rorollin          #+#    #+#             */
/*   Updated: 2025/07/19 18:08:30 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	print_token(t_token token)
{
	printf("\n Token content : \"%s\" \n token Type : %i\n", token.content, token.type);
	
}

void	print_token_list(t_token_list *list)
{
	t_token_list *temp;

	temp = list;
	while (temp != NULL && temp->content != NULL)
	{
		print_token(*(t_token *) temp->content);
		temp = temp->next;
	}

}

static const char	*get_state_name(t_ps_state state)
{
	if (state == STATE_NORMAL)
		return ("STATE_NORMAL");
	if (state == STATE_SQUOTE)
		return ("STATE_SQUOTE");
	if (state == STATE_DQUOTE)
		return ("STATE_DQUOTE");
	if (state == STATE_OP)
		return ("STATE_OP");
	return ("UNKNOWN_STATE");
}

void	print_parser_state(t_parser *parser)
{
	printf("=== Parser State ===\n");
	printf("State: %s\n", get_state_name(parser->state));
	printf("Input: |%s|\n", parser->input);
	printf("Current Position: |%s|\n", parser->crnt_pos);
	printf("Start Position: |%s|\n", parser->start_pos);
	if (parser->crnt_token)
	{
		printf("Current Token:\n");
		print_token(*(parser->crnt_token));
	}
	else
	{
		printf("Current Token: NULL\n");
	}
	printf("====================\n");
}
static const char *get_node_type_string(t_node_type type)
{
	switch (type)
	{
		case NODE_COMMAND:
			return "COMMAND";
		case NODE_PIPE:
			return "PIPE";
		case NODE_REDIR_IN:
			return "REDIR_IN";
		case NODE_REDIR_OUT:
			return "REDIR_OUT";
		case NODE_REDIR_APPEND:
			return "REDIR_APPEND";
		case NODE_ERROR:
			return "ERROR";
		default:
			return "UNKNOWN";
	}
}

static void print_ast_helper(t_ast *node, int depth)
{
	int i;

	if (!node)
	{
		for (i = 0; i < depth; i++)
			printf("  ");
		printf("(null)\n");
		return;
	}

	// Print indentation
	for (i = 0; i < depth; i++)
		printf("  ");

	// Print node type
	printf("%s", get_node_type_string(node->type));

	// Print token if present
	if (node->token)
	{
		printf(" - ");
		print_token(*node->token);
	}
	else
		printf("\n");

	// Recursively print children
	if (node->left || node->right)
	{
		for (i = 0; i < depth; i++)
			printf("  ");
		printf("├─ left:\n");
		print_ast_helper(node->left, depth + 1);

		for (i = 0; i < depth; i++)
			printf("  ");
		printf("└─ right:\n");
		print_ast_helper(node->right, depth + 1);
	}
}

void print_ast(t_ast *root)
{
	printf("AST Structure:\n");
	print_ast_helper(root, 0);
}
