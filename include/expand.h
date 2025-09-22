/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:14:20 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 17:35:38 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
# include "struct.h"

t_var			*var_search(char *key);
char			*var_expand_end(const char *key);
t_token_list	*token_join(t_token_list *first);
#endif
