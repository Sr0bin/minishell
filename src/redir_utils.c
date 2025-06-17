/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:11:29 by lserodon          #+#    #+#             */
/*   Updated: 2025/06/17 10:32:47 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/exec.h"

int	set_input_fd(t_cmd *cmd)
{
	int	fd_in;

	fd_in = -1;
	if (cmd->fd_in.fd)
	{
		fd_in = open(cmd->fd_in.fd, O_RDONLY);
		if (fd_in < 0)
			ft_error(cmd, "minishell: fd_in", 1);
		if (dup2(fd_in, STDIN_FILENO) == -1)
			ft_error(cmd, "minishell: dup2", 1);
	}
	return (fd_in);
}

int	set_output_fd(t_cmd *cmd)
{
	int	fd_out;

	fd_out = -1;
	if (cmd->fd_out.fd)
	{
		if (cmd->fd_out.redir_type == REDIR_APPEND)
			fd_out = open(cmd->fd_out.fd,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (cmd->fd_out.redir_type == REDIR_OUTPUT)
			fd_out = open(cmd->fd_out.fd,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
			ft_error(cmd, "minishell: fd_out", 1);
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			ft_error(cmd, "minishell: dup2", 1);
	}
	return (fd_out);
}
