/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:48:12 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/04 21:56:52 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "minishell.h"

t_redir	*create_redir(t_redir_type type, char *filename)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (redir == NULL)
		return (ft_error("Redir token failed", MALLOC_FAILED));
	redir->type = type;
	redir->filename = filename;
	return (redir);
}

t_redir	*redir_token_create(t_token_list *tkn_lst)
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
	{
		redir_type = REDIR_HEREDOC;
		return (heredoc_create_fd());
	}
	filename = ft_strdup(lst_to_tkn(tkn_lst->next)->content);
	if (filename == NULL)
		return (ft_error("strdup failed in redir_token", MALLOC_FAILED));
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
	free(redir);
	return (NULL);
}

void	*redir_destroy(t_redir_list **redir_list, t_redir **redir)
{
	ft_lstclear(redir_list, (void (*)) free_redir);
	free_redir(*redir);
	return (NULL);
}
