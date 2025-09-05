/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 08:10:16 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/05 10:36:42 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_child(const char *msg, int exit_code)
{
	if (errno)
		perror(msg);
	else
		ft_putendl_fd(msg, 2);
	exit_code_update(exit_code);
	exit(exit_code);
}

void	ft_error(const char *msg, int exit_code)
{
	if (errno)
		perror(msg);
	else
		ft_putendl_fd(msg, 2);
	exit_code_update(exit_code);
}

void	*free_exec(void *exec_data)
{
	if (exec_data == NULL)
		return (NULL);
	free_envp(((t_exec_data *) exec_data)->envp);
	free_exec_data(exec_data);
	return (NULL);
}

void	ft_fatal_error(void *arg, const char *msg, int exit_code, void *(*f)(void *))
{
	if (!arg)
		exit(exit_code);
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd((char *)msg, 2);
	perror("Errno ");
	f(arg);
	exit (exit_code);
}
