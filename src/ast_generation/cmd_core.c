/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:56:00 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/18 15:52:00 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	cmd_create(t_token_list *tkn_lst)
{
	t_cmd	cmd;

	cmd.redir = redir_list_create(tkn_lst);
	cmd.path = ft_strdup(lst_to_tkn(tkn_lst)->content);
	cmd.args = NULL;
	cmd.envp = NULL;
	return (cmd);
}

void	*free_parser_cmd(t_cmd cmd)
{

	ft_lstclear(&cmd.redir, (void (*)) free_redir);
	free(cmd.path);
	return (NULL);
}

