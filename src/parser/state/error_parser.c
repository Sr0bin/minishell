/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 18:16:04 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 17:18:34 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*parser_handle_error(t_parser *p, t_token_list **final_list)
{
	if (p->error_code == SYNTAX_ERROR)
		printf("Please close quotes !\n");
	else if (p->error_code == MALLOC_FAIL)
		printf("Malloc failed !\n");
	if (p->error_code != 0)
		token_list_destroy(final_list);
	return (NULL);
}

void	*parser_update_error(t_parser *p, char error_code)
{
	p->error_code = error_code;
	return (NULL);
}
