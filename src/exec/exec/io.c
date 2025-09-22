/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:09:28 by lserodon          #+#    #+#             */
/*   Updated: 2025/09/22 18:03:46 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"

int	open_redir_file(t_redir *redir)
{
	if (redir->type == REDIR_OUTPUT)
		return (open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (redir->type == REDIR_APPEND)
		return (open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else if (redir->type == REDIR_INPUT)
		return (open(redir->filename, O_RDONLY));
	else if (redir->type == REDIR_HEREDOC)
		return (redir->s_heredoc.read);
	return (0);
}

int	apply_dup2_close(int fd, t_redir_type type)
{
	if (type == REDIR_INPUT || type == REDIR_HEREDOC)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			ft_error("minishell: dup2 failed\n", 1);
			return (-1);
		}
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			ft_error("minishell: dup2 failed\n", 1);
			return (-1);
		}
	}
	return (0);
}

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
		fd = open_redir_file(redir);
		if (fd < 0)
		{
			ft_error("minishell\n", 1);
			return (-1);
		}
		if (apply_dup2_close(fd, redir->type) == -1)
			return (-1);
		close(fd);
		node = node->next;
	}
	return (0);
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
