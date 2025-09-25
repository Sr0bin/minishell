/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:09:13 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/25 22:00:32 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

int	add_new_var(t_exec_data *exec_data, t_list *new_lst, t_var *var)
{
	int		check_env;

	check_env = check_in_env(exec_data->envp, var);
	if (check_env == 0)
	{
		new_lst = ft_lstnew(var);
		if (!new_lst)
		{
			free(var);
			ft_error("minishell: malloc failed\n", 1);
			return (-1);
		}
		ft_lstadd_back(&exec_data->envp, new_lst);
	}
	else if (check_env == -1)
	{
		free_var(var);
		return (-1);
	}
	else
		free_var(var);
	return (0);
}

int	export_with_args(t_exec_data *exec_data, char **cmd)
{
	int		i;
	t_var	*var;
	t_list	*new_lst;

	i = 1;
	new_lst = NULL;
	while (cmd[i])
	{
		var = 0;
		if (check_export_var(cmd[i]) == 0)
		{
			var = malloc(sizeof(t_var));
			if (!var)
			{
				ft_error("minishell: malloc failed\n", 1);
				return (-1);
			}
			if (parse_args(cmd[i], var) == -1)
				return (-1);
			if (add_new_var(exec_data, new_lst, var) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
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
	exec_data->envp = head;
	print_export_list(head);
}

int	ft_export(t_exec_data *exec_data, t_cmds cmd)
{
	if (count_nbr_args(cmd.cmd) <= 1)
		export_without_args(exec_data);
	else
	{
		if (export_with_args(exec_data, cmd.cmd) == -1)
			return (-1);
	}
	return (0);
}
