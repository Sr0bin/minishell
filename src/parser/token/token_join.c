/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:03:23 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 13:03:59 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list	*token_join(t_token_list *first, t_token_list *deleted)
{
	t_token	*frst_tkn;
	t_token	*del_tkn;
	char	*ret;

	frst_tkn = lst_to_tkn(first);
	del_tkn = lst_to_tkn(deleted);
	if (del_tkn->to_join != 1)
		frst_tkn->to_join = 0;
	token_clean_quote(del_tkn);
	ret = ft_strcat(&frst_tkn->content, del_tkn->content);
	if (ret == NULL)
		return (NULL);
	ft_lstpop(&first, (void *) free);
	return (first);
}
