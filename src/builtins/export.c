/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:09:13 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/17 16:40:22 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_export(t_env **env, char **args)
{
	if (!args || !args[0])
		export_without_args(*env);
	else
		export_with_args(env, args);
}
