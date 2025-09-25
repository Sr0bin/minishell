/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:21:09 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/25 22:13:22 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* ----- LIBRARIES ----- */
# include <stdio.h>
# include "../libft/include/libft.h"
# include "exec/ast_to_cmds.h"
# include "exec/exec.h"
# include "context.h"

typedef struct s_list	t_env;

/* ----- BUILTINS.C ----- */
int		exec_builtins(t_exec_data *exec_data, int i);
t_list	*envp_to_list(char **envp);
t_var	*create_var(char *env);
int		run_builtins(t_exec_data *exec_data, int i);

/* ----- CD.C ----- */
int		ft_cd(t_exec_data *exec_data, t_cmds cmd);
int		execute_ft_cd(t_exec_data *exec_data, t_cmds cmd);
char	*ft_cd_set_path(t_exec_data *exec_data, t_cmds cmd);
int		ft_cd_update_env(t_exec_data *exec_data, char *old_pwd,
			char *new_pwd, t_cmds cmd);
int		update_env(t_exec_data *exec_data, const char *key, const char *value);
int		create_new_var(t_exec_data *exec_data, const char *key,
			const char *value);

/* ----- ECHO.C ----- */
int		ft_echo(t_cmds cmd);
int		newline(char *str);

/* ----- ENV.C ----- */
int		ft_env(t_env *env);

/* ----- EXIT.C ----- */
int		ft_exit(t_exec_data *exec_data, t_cmds cmd);

/* ----- EXPORT.C ----- */
int		is_sorted(t_env *env);
int		check_export_var(char *args);
int		check_in_env(t_env *env, t_var *var);
int		ft_export(t_exec_data *exec_data, t_cmds cmd);
void	check_var(t_list **env, char **args);
void	delete_var(t_list **env, char *args);
int		export_with_args(t_exec_data *exec_data, char **args);
void	export_without_args(t_exec_data *exec_data);
void	free_var(void	*content);
void	ft_swap(t_env *a, t_env *b);
int		parse_args(char *arg, t_var *var);
void	print_export_list(t_env *env);
int		ft_pwd(void);
int		ft_unset(t_list **env, t_cmds cmd);

#endif
