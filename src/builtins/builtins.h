/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:21:09 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/17 16:30:44 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* ----- LIBRARIES ----- */
# include <stdio.h>
# include "../../libft/include/libft.h"

typedef struct s_list	t_env;

typedef struct s_var
{
	char	*key;
	char	*value;
}			t_var;

/* ----- FUNCTIONS.C ----- */
void	ft_echo(int argc, char **argv);
void	ft_cd(int argc, char **argv);
void	ft_pwd(void);
void	ft_env(t_list *env);
void	ft_unset(t_list **env, char **args);
void	check_var(t_list **env, char **args);
void	delete_var(t_list **env, char *args);
void	free_var(void	*content);
void	ft_export(t_env **env, char **args);
void	export_with_args(t_env **env, char **args);
int		check_in_env(t_env *env, t_var *var);
void	parse_args(char *arg, t_var *var);
int		check_export_var(char *args);
void	print_export_list(t_env *env);
void	export_without_args(t_env *env);
void	ft_swap(t_env *a, t_env *b);
int		is_sorted(t_env *env);

#endif