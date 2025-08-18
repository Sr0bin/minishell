/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:13:51 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/20 14:40:32 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "struct.h"
# include "../../libft/include/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef enum s_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_PIPE,
}			t_redir_type;

typedef struct s_cmd
{
	t_redir	fd_in;
	t_redir	fd_out;
	char	*path;
	char	**cmd;
	char	**envp;
}	t_cmd;

void	exec_cmd(t_cmd *cmd);
int		set_input_fd(t_cmd *cmd);
void	exec_fork(t_cmd *cmd);
int		set_output_fd(t_cmd *cmd);
char	*find_path(t_cmd *cmd);
char	*get_env_path(t_cmd *cmd, char **envp);
void	free_array(char **array);
void	exec_single_cmd(t_ast_node *root, char	**envp);
void	init_cmd(t_cmd *cmd, t_ast_node *node);
void	fill_cmd(t_cmd *cmd, t_token *token);
void	fill_redir(t_cmd *cmd, t_node_type redir, t_ast_node *node);
int		count_nbr_args(t_token *token);
void	ft_error(t_cmd *cmd, const char *msg, int exit_code);
void	free_cmds(t_cmd *cmd);

#endif