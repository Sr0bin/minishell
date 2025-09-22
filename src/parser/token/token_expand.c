/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:23:15 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 12:38:06 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/token.h"

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

t_token_list	*token_join(t_token_list *first, t_token_list *deleted)
{
	t_token	*frst_tkn;
	t_token	*del_tkn;
	char	*ret;

	frst_tkn = lst_to_tkn(first);
	del_tkn = lst_to_tkn(deleted);
	if (del_tkn->to_join != 1)
		frst_tkn->to_join = 0;
	// TODO : add expand when the global context works
	// token_expand(del_tkn, env);
	token_clean_quote(del_tkn);
	ret = ft_strcat(&frst_tkn->content, del_tkn->content);
	if (ret == NULL)
		return (NULL);
	ft_lstpop(&first, (void *) free);
	return (first);
}

static	char *expanded_string(char *key)
{
	t_var	*found_var;
	char	*var_value;

	if (ft_strcmp(key, "$?") == 0)
	{
		var_value = ft_itoa(exit_code_read());
		if (var_value == NULL)
			return (NULL);
	}
	else
	{
		found_var = var_search(context_read()->env, &key[1]);
		if (found_var == NULL)
			return (key);
		var_value = found_var->value;
	}
	return (var_value);
}

t_token *token_expand(t_token *tkn)
{
	char	*var_value;
	char	*dollar;
	char	*space;
	size_t	len_space;

	if (tkn->content[0] == '\'')
		return (tkn);
	dollar = ft_strchr(tkn->content, '$');
	if (dollar == NULL)
		return (tkn);
	if (ft_strcmp("$", dollar) == 0)
		return (tkn);
	var_value = expanded_string(dollar);
	if (var_value == dollar)
		return (tkn);
	if (var_value == NULL)
		return (NULL);
	ft_strrsz(&tkn->content, ft_strlen(tkn->content) + ft_strlen(var_value));
	if (tkn->content == NULL)
		return (NULL);
	dollar = ft_strchr(tkn->content, '$');
	space = var_expand_end(dollar); 
	len_space = ft_strlen(space);
	ft_memmove(dollar + ft_strlen(var_value), space, ft_strlen(space));
	ft_memmove(dollar, var_value, ft_strlen(var_value));
	dollar[ft_strlen(var_value) + len_space] = '\0';
	return (tkn);
}
