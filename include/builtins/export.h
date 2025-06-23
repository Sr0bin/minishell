/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:43:11 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/20 11:22:48 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

typedef struct s_list	t_env;
typedef struct s_var	t_var;
 
int		check_export_var(char *args);
int		check_in_env(t_env *env, t_var *var);
int		is_sorted(t_env *env);
void	check_var(t_list **env, char **args);
void	delete_var(t_list **env, char *args);
void	export_with_args(t_env **env, char **args);
void	export_without_args(t_env *env);
void	free_var(void	*content);
void	ft_export(t_env **env, char **args);
void	ft_swap(t_env *a, t_env *b);
void	parse_args(char *arg, t_var *var);
void	print_export_list(t_env *env);

#endif