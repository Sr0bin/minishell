/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:23:15 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/28 19:23:48 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	char_end_expand(char c)
{
	if (char_type(c) == CHAR_WHITESPACE 
		|| char_type(c) == CHAR_EOF 
		|| char_type(c) == CHAR_NEWLINE
		|| char_type(c) == CHAR_DQUOTE
		|| char_type(c) == CHAR_SQUOTE
		|| char_type(c) == CHAR_OPERATOR)
		return (1);
	return (0);
}

char	*var_expand_end(const char *key)
{
	while (*key != '\0')
	{
		if (char_end_expand(*key) == 1)
			return ((char *) key);
		key++;
	}
	return ((char *) key);

}

t_token *token_expand(t_token *tkn, t_env *env)
{
	// t_ps_state state;
	t_var	*found_var;
	char	*dollar;
	char	*space;
	size_t	new_size;


	// if (tkn->content[0] == '"')
	// 	state = STATE_DQUOTE;
	if (tkn->content[0] == '\'')
		return (tkn);
	dollar = ft_strchr(tkn->content, '$');
	if (dollar == NULL)
		return (tkn);
	found_var = var_search(env, &dollar[1]);
	if (found_var == NULL)
		return (tkn);
	new_size = ft_strlen(tkn->content) + ft_strlen(found_var->value);
	ft_strrsz(&tkn->content, new_size);
	dollar = ft_strchr(tkn->content, '$');
	space = var_expand_end(dollar); 
	ft_memcpy(dollar + ft_strlen(found_var->value), space, ft_strlen(tkn->content) - ft_strlen(dollar));
	ft_memcpy(dollar, found_var->value, ft_strlen(found_var->value));
	// (void) state;
	return (tkn);
}
