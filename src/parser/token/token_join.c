/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:03:23 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/25 18:45:59 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list	*token_join(t_token_list *first)
{
	t_token	*frst_tkn;
	t_token	*scnd_tkn;
	char	*ret;

	frst_tkn = lst_to_tkn(first);
	scnd_tkn = lst_to_tkn(first->next);
	if (scnd_tkn->to_join == 0)
		frst_tkn->to_join = 0;
	token_expand_loop(scnd_tkn);
	token_clean_quote(scnd_tkn);
	ret = ft_strcat(&frst_tkn->content, scnd_tkn->content);
	if (ret == NULL)
		return (NULL);
	ft_lstpop(&first, (void *) free);
	if (frst_tkn->to_join == 1)
		return (token_join(first));
	return (first);
}
