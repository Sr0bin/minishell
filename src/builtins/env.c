/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:15:57 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/03 15:30:09 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_env(t_list *env)
{
	while (env && env->next != NULL)
	{
		printf("%s%s", env->content.key, env->content.value);
		env->next;
	}
}