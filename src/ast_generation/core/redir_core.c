/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:48:12 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 09:20:44 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
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

static t_redir_type	redir_type_token(t_token_list *tkn_lst)
{
	if (lst_to_tkn(tkn_lst)->type == TOKEN_REDIR_OUT)
		return (REDIR_OUTPUT);
	if (lst_to_tkn(tkn_lst)->type == TOKEN_REDIR_IN)
		return (REDIR_INPUT);
	if (lst_to_tkn(tkn_lst)->type == TOKEN_REDIR_APPEND)
		return (REDIR_APPEND);
	if (lst_to_tkn(tkn_lst)->type == TOKEN_HEREDOC)
		return (REDIR_HEREDOC);
	return (-1);
}

t_redir	*redir_token_create(t_token_list *tkn_lst)
{
	t_redir			*redir;
	char			*filename;
	t_redir_type	redir_type;

	if (tkn_lst == NULL)
		return (NULL);
	if (tkn_lst->next == NULL || lst_to_tkn(tkn_lst->next)->type != TOKEN_WORD)
		return (NULL);
	redir_type = redir_type_token(tkn_lst);
	if (redir_type == REDIR_HEREDOC)
		return (heredoc_create_fd(tkn_lst));
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
	if (redir != NULL && redir->type != REDIR_HEREDOC)
		free((redir)->filename);
	if (redir != NULL && redir->type == REDIR_HEREDOC)
		close(redir->s_heredoc.read);
	free(redir);
	return (NULL);
}

void	*redir_destroy(t_redir_list **redir_list, t_redir **redir)
{
	ft_lstclear(redir_list, (void (*)) free_redir);
	if (redir != NULL && *redir != NULL)
		free_redir(*redir);
	return (NULL);
}
