/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:49:24 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/04 21:51:29 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_list	*redir_list_create(t_token_list *tkn_lst)
{
	t_token_list	*crnt_tkn;
	t_redir_list	*redir_list;
	t_redir_list	*list_temp;
	t_redir	*crnt_redir;
	
	redir_list = NULL;
	crnt_redir = NULL;
	crnt_tkn = redir_find_first(tkn_lst);
	if (crnt_tkn == NULL)
		return (NULL);
	crnt_redir = redir_token_create(crnt_tkn);
	if (crnt_redir == NULL)
		return (ft_error("Redir token creation failed", MALLOC_FAILED));
	redir_list = ft_lstnew(crnt_redir);
	if (redir_list == NULL)
		return (redir_destroy(&redir_list, &crnt_redir));
	crnt_tkn = redir_find_first(crnt_tkn->next);
	while (crnt_tkn != NULL)
	{
		crnt_redir = redir_token_create(crnt_tkn);
		list_temp = ft_lstnew(crnt_redir);
		if (crnt_redir == NULL || list_temp == NULL)
			return (redir_destroy(&redir_list, &crnt_redir));
		ft_lstadd_back(&redir_list, list_temp);
		crnt_tkn = redir_find_first(crnt_tkn->next);
	}
	return (redir_list);
}
