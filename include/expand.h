/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:14:20 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 13:14:57 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
#include "struct.h"

t_var	*var_search(t_env *env, char *key);
t_token_list	*token_join(t_token_list *first);
#endif

