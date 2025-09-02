/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:22:49 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/02 19:58:07 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	print_token(t_token token)
{
	printf("Token content : \"%s\"\n", token.content);
	if (token.to_join == 1)
		printf("To be joined!\n");
	/*printf("Token Type : %i\n",token.type);*/
	
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
		case NODE_FILE:
			return "FILE";
		default:
			return "UNKNOWN";
	}
}
void print_redir(t_redir *redir)
{
    if (!redir)
    {
        printf("Redirection: NULL\n");
        return;
    }

    printf("Redirection: ");
    
    switch (redir->type)
    {
        case REDIR_INPUT:
            printf("INPUT (<) ");
            break;
        case REDIR_OUTPUT:
            printf("OUTPUT (>) ");
            break;
        case REDIR_APPEND:
            printf("APPEND (>>) ");
            break;
        case REDIR_HEREDOC:
            printf("HEREDOC (<<) ");
            break;
        case REDIR_PIPE:
            printf("PIPE (|) ");
            break;
        default:
            printf("UNKNOWN ");
            break;
    }
    
    if (redir->filename)
        printf("-> '%s'\n", redir->filename);
    else
        printf("-> (no filename)\n");
}

static void print_cmd_details(t_cmd *cmd, int depth)
{
	int i;
	
	/*if (cmd->path)*/
	/*{*/
	/*	for (i = 0; i < depth; i++)*/
	/*		printf("│  ");*/
	/*	printf("├─ path: %s\n", cmd->path);*/
	/*}*/
	
	if (cmd->args)
	{
		for (i = 0; i < depth; i++)
			printf("│  ");
		printf("├─ args: ");
		for (i = 0; cmd->args[i]; i++)
		{
			if (i > 0)
				printf(", ");
			printf("%s", cmd->args[i]);
		}
		printf("\n");
	}
	
	if (cmd->redir)
	{
		for (i = 0; i < depth; i++)
			printf("│  ");
		printf("├─ redirections:\n");
		print_redir_list(cmd->redir);
	}
}

static void print_ast_helper(t_ast *node, int depth)
{
	int i;
	if (!node)
	{
		for (i = 0; i < depth; i++)
			printf("│  ");
		printf("(null)\n");
		return;
	}
	
	// Print indentation with vertical lines
	for (i = 0; i < depth; i++)
		printf("│  ");
	
	// Print node type
	printf("%s\n", get_node_type_string(node->type));
	
	// Print additional details based on node type
	if (node->type == NODE_COMMAND)
	{
		print_cmd_details(&node->cmd, depth);
	}
	
	// Recursively print children based on node type
	if (node->type == NODE_PIPE)
	{
		for (i = 0; i < depth; i++)
			printf("│  ");
		printf("├─ left:\n");
		print_ast_helper(node->s_pipe.left, depth + 1);
		
		for (i = 0; i < depth; i++)
			printf("│  ");
		printf("└─ right:\n");
		print_ast_helper(node->s_pipe.right, depth + 1);
	}
}
void print_redir_list(t_list *redir_list)
{
    int i = 0;
    t_list *current;
    
    if (!redir_list)
    {
        printf("Redirection list: empty\n");
        return;
    }
    
    printf("Redirection list:\n");
    current = redir_list;
    
    while (current)
    {
        printf("[%d] ", i);
        print_redir((t_redir *)current->content);
        current = current->next;
        i++;
    }
    
    printf("Total redirections: %d\n", i);
}
void print_ast(t_ast *root)
{
	printf("AST Structure:\n");
	print_ast_helper(root, 0);
}
