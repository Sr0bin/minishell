/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:35:19 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/28 18:30:29 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "../struct.h"

t_token			*token_create(char *text, t_token_type type);
t_token_list	*token_list_create(t_token *first);
t_token_list	*token_list_clean(t_token_list **list, t_env *env);
t_token			*assign_token_type(t_token *token);
t_token			*token_expand(t_token *tkn, t_env *env);
t_token			*lst_to_tkn(t_token_list *tkn_list);
void			*token_list_add(t_token_list **list, t_token_list *token);
void			*token_destroy(t_token *token);
void			*token_ptr_destroy(t_token **token);
void			*token_list_destroy(t_token_list **tkn_lst);
#endif
