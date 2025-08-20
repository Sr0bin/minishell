/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:47:55 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/20 18:02:38 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes/multipipes.h"

int	count_commands(t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (1);
	else if (node->type == NODE_PIPE)
		return (count_commands(node->s_pipe.left)
			+ count_commands(node->s_pipe.right));
	return (0);
}

int	count_nbr_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
