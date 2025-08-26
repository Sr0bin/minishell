/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:56:00 by rorollin          #+#    #+#             */
/*   Updated: 2025/08/26 16:49:12 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_generation/ast.h"
#include "minishell.h"

t_token_list	*token_list_skip_redir(t_token_list *tkn_lst)
{
	t_token_list	*pipe_first;

	pipe_first = pipe_find_first(tkn_lst);
	while (tkn_lst != pipe_first)
	{
		if (token_list_type_redir(tkn_lst) == 0)
			return (tkn_lst);
		tkn_lst = tkn_lst->next;
		if (tkn_lst != NULL && tkn_lst != pipe_first)
			tkn_lst = tkn_lst->next;
	}
	if (tkn_lst == pipe_first || tkn_lst == NULL)
		return (NULL);
	return (tkn_lst);
}

size_t	args_cmd_count(t_token_list *tkn_lst)
{
	size_t			i;
	t_token_list	*pipe_first;

	i = 0;
	pipe_first = pipe_find_first(tkn_lst);
	tkn_lst = token_list_skip_redir(tkn_lst);
	while (tkn_lst != NULL && tkn_lst != pipe_first)
	{
		tkn_lst = tkn_lst->next;
		tkn_lst = token_list_skip_redir(tkn_lst);
		i++;
	}
	return (i);
}

t_cmd	cmd_free_args(t_cmd cmd)
{
	char	**ptr;

	ptr = cmd.args;
	while (*ptr != NULL)
	{
		free(*ptr);
		ptr++;
	}
	free(cmd.args);
	return ((t_cmd){0});
}

t_cmd	cmd_create(t_token_list *tkn_lst)
{
	char			**crnt_arg;
	t_cmd			cmd;
	t_token_list	*pipe_first;

	cmd.redir = redir_list_create(tkn_lst);
	cmd.args = ft_calloc(args_cmd_count(tkn_lst) + 1, sizeof(char *));
	pipe_first = pipe_find_first(tkn_lst);
	crnt_arg = cmd.args;
	tkn_lst = token_list_skip_redir(tkn_lst);
	while (tkn_lst != NULL && tkn_lst != pipe_first)
	{
		if (tkn_lst != NULL)
		{
			*crnt_arg = ft_strdup(lst_to_tkn(tkn_lst)->content);
			if (crnt_arg == NULL)
				return (cmd_free_args(cmd));
			crnt_arg++;
		}
		tkn_lst = tkn_lst->next;
		tkn_lst = token_list_skip_redir(tkn_lst);
	}
	return (cmd);
}

void	*free_parser_cmd(t_cmd cmd)
{
	ft_lstclear(&cmd.redir, (void (*)) free_redir);
	cmd_free_args(cmd);
	return (NULL);
}
