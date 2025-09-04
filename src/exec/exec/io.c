/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:09:28 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/04 19:22:16 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"

int	apply_redirections(t_exec_data *exec_data, int i)
{
	int		fd;
	t_list	*node;
	t_redir	*redir;

	fd = -1;
	node = exec_data->cmds[i].redir;
	while (node)
	{
		redir = (t_redir *)node->content;
		if (redir->type == REDIR_OUTPUT)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == REDIR_APPEND)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == REDIR_INPUT)
			fd = open(redir->filename, O_RDONLY);
		else if (redir->type == REDIR_HEREDOC)
				fd = redir->s_heredoc.read;
		if (fd < 0)
			return (-1);
		if (redir->type == REDIR_INPUT || redir->type == REDIR_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close (fd);
		node = node->next;
	}
	return (0);
}

void	setup_io(t_exec_data *exec_data, int i)
{
	if (i > 0)
		dup2(exec_data->fd[i - 1][0], STDIN_FILENO);
	if (i < exec_data->nb_cmds - 1)
		dup2(exec_data->fd[i][1], STDOUT_FILENO);
	if (apply_redirections(exec_data, i) < 0)
		ft_fatal_error(exec_data, "redirections failed", 1, &free_exec);
}

void	close_parent_fds(t_exec_data *exec_data, int i)
{
	if (i > 0)
	{
		close(exec_data->fd[i - 1][0]);
		exec_data->fd[i - 1][0] = -1;
	}
	if (i < exec_data->nb_cmds - 1)
	{
		close(exec_data->fd[i][1]);
		exec_data->fd[i][1] = -1;
	}
}
