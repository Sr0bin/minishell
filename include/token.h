/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:35:19 by rorollin          #+#    #+#             */
/*   Updated: 2025/07/19 15:37:55 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "struct.h"

t_token	*create_token(char *text, t_token_type type);
t_token_list	*create_token_list(t_token *first);
t_token_list	*clean_token_list(t_token_list **list);
t_token	*assign_token_type(t_token *token);
void	*add_token(t_token_list **list, t_token_list *token);
void	*free_token(t_token *token);
void	*free_token_list(t_token_list **t_list);
#endif

