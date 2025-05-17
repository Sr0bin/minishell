/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:21:09 by lserodon          #+#    #+#             */
/*   Updated: 2025/05/17 14:10:14 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* ----- LIBRARIES ----- */
#include <stdio.h>
#include "../../libft/include/libft.h"
#include "../pipex/pipex.h"

/* ----- FUNCTIONS.C ----- */
void    ft_echo(int argc, char **argv);
void	ft_cd(int argc, char **argv);
void	ft_pwd(void);

#endif