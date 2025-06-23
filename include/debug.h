/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:32:23 by rorollin          #+#    #+#             */
/*   Updated: 2025/06/23 17:13:33 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H
# include "struct.h"
void	print_token(t_token token);
void	print_token_list(t_token_list *list);
void	print_parser_state(t_parser *parser);
#endif

