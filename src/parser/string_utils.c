/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:54:37 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/20 15:55:15 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_char_type	safe_char_type(t_parser *p, int offset)
{
	ptrdiff_t	begin_len;
	int			end_len;

	begin_len = p->crnt_pos - p->input;
	end_len = (int) ft_strlen(p->crnt_pos);
	if (offset >= 0)
	{
		if (offset > end_len)
			return (CHAR_ERROR);
		return (char_type(p->crnt_pos[offset]));
	}
	if (offset < 0)
	{
		if ((offset * -1) > begin_len)
			return (CHAR_ERROR);
		return (char_type(p->crnt_pos[offset]));
	}
	return (char_type(p->crnt_pos[offset]));
}

void	remove_char(char *text)
{
	ft_strlcpy(text, text + 1, ft_strlen(text));
}
