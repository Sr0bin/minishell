/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:56:00 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 16:01:07 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_generation/ast.h"
#include "minishell.h"
#include "parsing/parsing_struct.h"

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

t_cmd	cmd_loop(t_token_list *tkn_lst, t_cmd *cmd, int *error)
{
	t_token_list	*pipe_first;
	char			**crnt_arg;

	crnt_arg = cmd->args;
	pipe_first = pipe_find_first(tkn_lst);
	tkn_lst = token_list_skip_redir(tkn_lst);
	while (tkn_lst != NULL && tkn_lst != pipe_first)
	{
		if (tkn_lst != NULL)
		{
			*crnt_arg = ft_strdup(lst_to_tkn(tkn_lst)->content);
			if (crnt_arg == NULL)
			{
				*error = MALLOC_FAIL;
				redir_destroy(&(cmd->redir), NULL);
				return (cmd_free_args(*cmd));
			}
			crnt_arg++;
		}
		tkn_lst = tkn_lst->next;
		tkn_lst = token_list_skip_redir(tkn_lst);
	}
	return (*cmd);
}

t_cmd	cmd_create(t_token_list *tkn_lst, int *error)
{
	t_cmd			cmd;

	cmd.redir = redir_list_create(tkn_lst);
	if (cmd.redir == NULL && redir_find_first(tkn_lst) != NULL)
	{
		*error = MALLOC_FAIL;
		return ((t_cmd){0});
	}
	cmd.args = ft_calloc(args_cmd_count(tkn_lst) + 1, sizeof(char *));
	if (cmd.args == NULL)
	{
		redir_destroy(&cmd.redir, NULL);
		*error = MALLOC_FAIL;
		return ((t_cmd){0});
	}
	cmd_loop(tkn_lst, &cmd, error);
	return (cmd);
}

void	*free_parser_cmd(t_cmd cmd)
{
	ft_lstclear(&cmd.redir, (void (*)) free_redir);
	cmd_free_args(cmd);
	return (NULL);
}
