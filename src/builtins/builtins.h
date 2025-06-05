/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:21:09 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/04 16:59:32 by lserodon         ###   ########.fr       */
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
void	ft_env(t_list *env);
void    ft_unset(t_list **env, char **args);
void	check_var(t_list **env, char **args);
void	delete_var(t_list **env, char *args);
void	free_var(void	*content);

typedef struct s_var
{
	char *key;
	char *value;
}	t_var;

#endif