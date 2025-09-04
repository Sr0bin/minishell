/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:07:32 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/03 01:23:18 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "structs.h"
# include "builtins/builtins.h"
# include "signals/signals.h"

/* ----- ENV_TO_ARRAY.C ----- */

char	**env_to_array(t_exec_data *exec_data);

/* ----- ERROR.C ----- */

void	ft_error(const char *msg, int exit_code);
void	ft_fatal_error(void *arg, const char *msg, int exit_code, void *(*f)(void *));

/* ----- EXEC.C ----- */

int		exec_single_cmd(t_exec_data *exec_data, int i);
int		exec_cmd(t_exec_data *exec_data, int i);
int		exec_pipex(t_exec_data *exec_data);
int		exec(t_ast *root);

/* ----- EXTERNAL.C ----- */

void	exec_external(t_exec_data *exec_data, int i);
void	check_path(t_exec_data *exec_data, int i);

/* ----- FREE_UTILS.C ----- */

void	free_array(char **array);
void	free_envp(t_env	*env);
void	free_cmds(t_exec_data *exec_data);
void	free_fds(int **fd, int nb_cmbs);
void	free_exec_data(t_exec_data *exec_data);
void	*free_exec(void *exec_data);

/* ------ IO.C ----- */

int		apply_redirections(t_exec_data *exec_data, int i);
void	setup_io(t_exec_data *exec_data, int i);
void	close_parent_fds(t_exec_data *exec_data, int i);

/* ----- PATH.C ----- */

char	*get_env_path( t_exec_data *exec_data);
char	**get_path_array(t_exec_data *exec_data);
char	*build_cmd_path(t_exec_data *exec_data, char *dir, int i);
char	*find_path(t_exec_data *exec_data, int i);
char	*check_access(t_exec_data *exec_data, char **array, char *path);

/* ----- PIPES.C ----- */

void	close_pipes(t_exec_data *exec_data);
void	init_pipes(t_exec_data *exec_data);

/* ----- STATUS.C ----- */

void	analyze_status(int status);
void	wait_cmd(t_exec_data *exec_data);

/* ----- UTILS.C ----- */

int		is_builtin(char *cmd);
char	*get_env_value(t_exec_data *exec_data, char *key);

#endif
