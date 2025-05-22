/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:14:56 by lserodon          #+#    #+#             */
/*   Updated: 2025/05/21 15:33:00 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char **array)
{
	int i;

	i = 0;

	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*find_path(char **envp, char *cmd)
{
	char	*path;
	char	*tmp_path;
	char	*cmd_path;
	char	**path_array;
	int		i;

	i = -1;
	while (envp && envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	}
	path_array = ft_split(path, ':');
	free (path);
	i = -1;
	while (path_array[++i])
	{
		tmp_path = ft_strjoin(path_array[i], (char *)"/");
		cmd_path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(cmd_path, X_OK) == 0)
		{
			free_array(path_array);
			return (cmd_path);
		}
		free(cmd_path);
	}
	return (NULL);
}

int	count_commands(t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (1);
	else if (node->type == NODE_PIPE)
		return (count_commands(node->left) + count_commands(node->right));
	return (0);
}

int		count_nbr_token(t_token *token)
{
	int i;

	i = 0;
	while (token)
	{
		i++;
		token = token->next;
	}
	return (i);
}

void	token_to_argv(t_token *token, char ***cmds, int *i)
{
	int	count;
	int	j;

	count = count_nbr_token(token);
	cmds[*i] = malloc(sizeof(char *) * (size_t)(count + 1));
	if (!cmds[*i])
		return ;
	j = 0;
	while (token)
	{
		cmds[*i][j] = ft_strdup(token->content);
		token = token->next;
		j++;
	}
	cmds[*i][j] = NULL;
}

void	fill_cmds(t_ast_node *node, char ***cmds, int *i)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		fill_cmds(node->left, cmds, i);
		fill_cmds(node->right, cmds, i);
	}
	else if (node->type == NODE_COMMAND)
	{
		token_to_argv(node->token_list, cmds, i);
		(*i)++;		
	}
}

char ***ast_to_cmds(t_ast_node *root)
{
	int	nbr_commands;
	int	i;
	char	***cmds;

	i = 0;
	nbr_commands = count_commands(root);
	cmds = malloc(sizeof(char **) * (size_t)(nbr_commands + 1));
	if (!cmds)
		return (NULL);
	fill_cmds(root, cmds, &i);
	cmds[i] = NULL;
	return (cmds);
}

void print_cmds(char ***cmds)
{
    if (!cmds)
    {
        printf("cmds is NULL\n");
        return;
    }

    for (int i = 0; cmds[i] != NULL; i++)
    {
        printf("Commande %d:\n", i);
        for (int j = 0; cmds[i][j] != NULL; j++)
        {
            printf("  argv[%d] = '%s'\n", j, cmds[i][j]);
        }
    }
}

// Fonction pour libérer la mémoire allouée par ast_to_cmds
void free_cmds(char ***cmds)
{
    if (!cmds)
        return;

    for (int i = 0; cmds[i] != NULL; i++)
    {
        for (int j = 0; cmds[i][j] != NULL; j++)
            free(cmds[i][j]);
        free(cmds[i]);
    }
    free(cmds);
}

int main(void)
{
	t_token token_echo = {TOKEN_WORD, "echo", NULL, NULL};
	t_token token_salut = {TOKEN_WORD, "salut", NULL, &token_echo};
	token_echo.next = &token_salut;

	t_token token_grep = {TOKEN_WORD, "grep", NULL, NULL};
	t_token token_a = {TOKEN_WORD, "a", NULL, &token_grep};
	token_grep.next = &token_a;

	t_token token_wc = {TOKEN_WORD, "wc", NULL, NULL};
	t_token token_c = {TOKEN_WORD, "-c", NULL, &token_wc};
	token_wc.next = &token_c;
	
	t_ast_node node_cmd1 = {NODE_COMMAND, NULL, NULL, &token_echo}; // echo salut
	t_ast_node node_cmd2 = {NODE_COMMAND, NULL, NULL, &token_grep}; // grep a
	t_ast_node node_cmd3 = {NODE_COMMAND, NULL, NULL, &token_wc};   // wc -c
	
	t_ast_node node_pipe1 = {NODE_PIPE, &node_cmd1, &node_cmd2, NULL}; // echo salut | grep a
	t_ast_node node_pipe2 = {NODE_PIPE, &node_pipe1, &node_cmd3, NULL}; // ... | wc -c
	
	char ***cmds = ast_to_cmds(&node_pipe2);

    // Affiche le résultat
    print_cmds(cmds);

    // Libère la mémoire
    free_cmds(cmds);
}
