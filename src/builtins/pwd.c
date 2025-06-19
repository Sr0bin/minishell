/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:57:41 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/19 13:48:32 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/builtins.h""

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 30

#endif

void	ft_pwd(void)
{
	char	buffer[BUFFER_SIZE];

	if (getcwd(buffer, BUFFER_SIZE) == NULL)
		perror("minishell: pwd");
	printf("%s\n", buffer);
}
/* 
int main()
{
	ft_pwd();
} */
