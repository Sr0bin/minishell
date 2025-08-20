/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:09:13 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/20 11:10:16 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

int	ft_export(t_env **env, char **args)
{
	if (!args || !args[0])
		export_without_args(*env);
	else
		export_with_args(env, args);
	return (1);
}
