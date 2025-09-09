/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:23:15 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/09 17:32:21 by rorollin         ###   ########.fr       */
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
	
	frst_tkn = lst_to_tkn(first);
	del_tkn = lst_to_tkn(deleted);
	if (del_tkn->to_join != 1)
		frst_tkn->to_join = 0;
	// TODO : add expand when the global context works
	// token_expand(del_tkn, env);
	token_clean_quote(del_tkn);
	ft_strcat(&frst_tkn->content, del_tkn->content);
	ft_lstpop(&first, (void *) free);
	return (first);
}

t_token *token_expand(t_token *tkn)
{
	// t_ps_state state;
	t_var	*found_var;
	char	*dollar;
	char	*space;
	size_t	new_size;
	size_t	len_space;


	// if (tkn->content[0] == '"')
	// 	state = STATE_DQUOTE;
	if (tkn->content[0] == '\'')
		return (tkn);
	dollar = ft_strchr(tkn->content, '$');
	if (dollar == NULL)
		return (tkn);
	//TODO: Put exit code here
	found_var = var_search(context_read()->env, &dollar[1]);
	if (found_var == NULL)
		return (tkn);
	new_size = ft_strlen(tkn->content) + ft_strlen(found_var->value);
	ft_strrsz(&tkn->content, new_size);
	dollar = ft_strchr(tkn->content, '$');
	space = var_expand_end(dollar); 
	len_space = ft_strlen(space);
	ft_memmove(dollar + ft_strlen(found_var->value), space, ft_strlen(space));
	ft_memmove(dollar, found_var->value, ft_strlen(found_var->value));
	dollar[ft_strlen(found_var->value) + len_space] = '\0';
	/*ft_memcpy(dollar + ft_strlen(found_var->value), space, ft_strlen(tkn->content) - ft_strlen(dollar));*/
	// (void) state;
	return (tkn);
}
