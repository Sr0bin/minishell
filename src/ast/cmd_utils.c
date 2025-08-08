/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:56:00 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/08 13:12:47 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	**create_redir_array()
{
	t_redir_array	*array;

	return (array);
}
void	*free_redir_array(t_redir_array **array)
{
	t_redir_array	*temp;

	temp = *array;
	while (*temp != NULL)
	{
		free_redir(temp);
		temp++;
	}
	free(*array);
	*array = NULL;
	return (NULL);
}

t_redir	*create_redir(t_redir_type type, char *filename)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (redir == NULL)
		return (NULL);
	redir->type = type;
	redir->filename = filename;
	return (redir);

}

void	*free_redir(t_redir **redir)
{
	free((*redir)->filename);
	free(*redir);
	*redir = NULL;
	return (NULL);
}
t_cmd	*create_cmd(t_redir_list *redir, char *path, char **args, char **envp)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->redir = redir;
	cmd->path = path;
	cmd->args = args;
	cmd->envp = envp;
	return (cmd);
}

void	*free_cmd(t_cmd **cmd)
{

	free(*cmd);
	*cmd = NULL;
	return (NULL);
}

