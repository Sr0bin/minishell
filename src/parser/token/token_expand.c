/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:23:15 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/24 15:01:43 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/token.h"

static int	char_end_expand(char c)
{
	if (char_type(c) == CHAR_DIGIT
		|| char_type(c) == CHAR_UNDERSCORE
		|| char_type(c) == CHAR_LETTER)
		return (0);
	return (1);
}

char	*var_expand_end(const char *key)
{
	if (*key == '?')
		return ((char *) key + 1);
	while (*key != '\0')
	{
		if (char_end_expand(*key) == 1)
			return ((char *) key);
		key++;
	}
	return ((char *) key);
}

static	char	*expanded_string(char *key, int *exit)
{
	t_var	*found_var;
	char	*var_value;

	if (ft_strncmp(key, "$?", 2) == 0)
	{
		*exit = 1;
		var_value = ft_itoa(exit_code_read());
		if (var_value == NULL)
			return (NULL);
	}
	else
	{
		*exit = 0;
		found_var = var_search(&key[1]);
		if (found_var == NULL)
			return (NULL);
		var_value = found_var->value;
	}
	return (var_value);
}

inline static void	expand_move(char *dollar, char *var_value, char *space)
{
	ft_memmove(dollar + ft_strlen(var_value), space, ft_strlen(space));
	if (var_value != NULL)
		ft_memmove(dollar, var_value, ft_strlen(var_value));
}

void	*token_expand(t_token *tkn)
{
	char	*var_value;
	char	*dollar;
	char	*space;
	size_t	len_space;
	int		exit;

	if (tkn->content[0] == '\'')
		return (tkn);
	dollar = ft_strchr(tkn->content, '$');
	if (dollar == NULL)
		return (tkn);
	var_value = expanded_string(dollar, &exit);
	if (var_value == dollar)
		return (var_value);
	ft_strrsz(&tkn->content, ft_strlen(tkn->content) + ft_strlen(var_value));
	if (tkn->content == NULL)
		return (NULL);
	dollar = ft_strchr(tkn->content, '$');
	space = var_expand_end(&dollar[1]);
	len_space = ft_strlen(space);
	expand_move(dollar, var_value, space);
	dollar[ft_strlen(var_value) + len_space] = '\0';
	if (exit != 0)
		free(var_value);
	return (tkn);
}
