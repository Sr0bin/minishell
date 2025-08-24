/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:07:58 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/24 11:23:06 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

void	free_var(void *content)
{
	t_var	*var;

	var = (t_var *)content;
	free(var->key);
	free(var->value);
	free(var);
}

void	delete_var(t_list **env, char *args)
{
	t_list	**current;
	t_list	*tmp;
	t_var	*var;

	current = env;
	while (*current)
	{
		var = (t_var *)(*current)->content;
		if (ft_strncmp(var->key, args, ft_strlen(args)) == 0)
		{
			tmp = *current;
			*current = (*current)->next;
			ft_lstdelone(tmp, free_var);
		}
		else
			current = &(*current)->next;
	}
}

void	check_var(t_list **env, char **args)
{
	int		i;

	i = 1;
	while (args[i])
	{
		delete_var(env, args[i]);
		i++;
	}
}

int	ft_unset(t_list **env, t_cmds cmd)
{
	if (!cmd.cmd[1])
		return (-1);
	else
		check_var(env, cmd.cmd);
	return (1);
}
