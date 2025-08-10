/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:56:00 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/10 19:33:04 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_redir	*create_redir_token(t_token_list *tkn_lst)
{
	t_redir	*redir;
	char	*filename;
	t_redir_type	redir_type;

	if (tkn_lst == NULL)
		return (NULL);
	if (tkn_lst->next == NULL || lst_to_tkn(tkn_lst->next)->type != TOKEN_WORD)
		return (NULL);
	if (lst_to_tkn(tkn_lst)->type == TOKEN_REDIR_OUT)
		redir_type = REDIR_OUTPUT;
	if (lst_to_tkn(tkn_lst)->type == TOKEN_REDIR_IN)
		redir_type = REDIR_INPUT;
	if (lst_to_tkn(tkn_lst)->type == TOKEN_REDIR_APPEND)
		redir_type = REDIR_APPEND;
	if (lst_to_tkn(tkn_lst)->type == TOKEN_HEREDOC)
		redir_type = REDIR_HEREDOC;
	filename = ft_strdup(lst_to_tkn(tkn_lst->next)->content);
	if (filename == NULL)
		return (NULL);
	redir = create_redir(redir_type, filename);
	if (redir == NULL)
	{
		free(filename);
		return (NULL);
	}
	return (redir);
}

void	*free_redir(t_redir *redir)
{
	if (redir != NULL)
		free((redir)->filename);
	free(redir);
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

void	*free_cmd(t_cmd cmd)
{

	ft_lstclear(&cmd.redir, (void (*)) free_redir);
	free(cmd.path);
	return (NULL);
}

