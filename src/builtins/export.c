/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:09:13 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/24 17:15:36 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

void	export_with_args(t_exec_data *exec_data, char **cmd)
{
	int		i;
	t_var	*var;

	i = 1;
	while (cmd[i])
	{
		var = 0;
		if (check_export_var(cmd[i]) == 0)
		{
			var = malloc(sizeof(t_var));
			if (!var)
				perror("minishell: malloc:");
			parse_args(cmd[i], var);
			if (!check_in_env(exec_data->envp, var))
				ft_lstadd_back(&exec_data->envp, ft_lstnew(var));
			else
			{
				free(var->key);
				if (var->value)
					free(var->value);
				free(var);
			}
		}
		i++;
	}
}

void	export_without_args(t_exec_data *exec_data)
{
	t_var	*var;
	t_var	*var2;
	int		sort;
	t_env	*head;

	sort = 0;
	head = exec_data->envp;
	while (!sort)
	{
		exec_data->envp = head;
		sort = 1;
		while (exec_data->envp && exec_data->envp->next)
		{
			var = (t_var *)exec_data->envp->content;
			var2 = (t_var *)exec_data->envp->next->content;
			if (ft_strcmp(var->key, var2->key) > 0)
			{
				ft_swap(exec_data->envp, exec_data->envp->next);
				sort = 0;
			}
			exec_data->envp = exec_data->envp->next;
		}
	}
	print_export_list(head);
}

int	ft_export(t_exec_data *exec_data, t_cmds cmd)
{
	if (count_nbr_args(cmd.cmd) <= 1)
		export_without_args(exec_data);
	else
		export_with_args(exec_data, cmd.cmd);
	return (1);
}
