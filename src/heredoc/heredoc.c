/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:45:01 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/04 19:21:07 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"
#include <fcntl.h>

#include <sys/stat.h>
#include <unistd.h>

static char	*temp_folder_path(int fd)
{
	char	*temp_path;
	char	*fd_ascii;

	temp_path = ft_strdup("/proc/self/fd/");
	fd_ascii = ft_itoa(fd);
	temp_path = ft_strcat(&temp_path, fd_ascii);
	return (temp_path);
}

t_redir	*heredoc_create_fd()
{
	t_redir	*redir;
	char	*temp_path;
	int	w_fd;
	int	r_fd;

	redir = ft_calloc(1, sizeof(t_redir));
	//TODO: protection
	redir->type = REDIR_HEREDOC;
	w_fd = open("/tmp", O_TMPFILE | O_WRONLY, 0600);
	if (w_fd < 0)
	{
		/*ft_error(exec_data_context(NULL, READ_EXEC_DATA), "Can't open temp file for Heredoc\n", 127);*/
		return (NULL);
	}
	write(w_fd, "test decriture", 20);
	temp_path = temp_folder_path(w_fd);
	r_fd = open(temp_path, O_RDONLY);
	free(temp_path);
	if (r_fd < 0)
	{
		close(w_fd);
		/*ft_error(exec_data_context(NULL, READ_EXEC_DATA), "Can't read temp file for Heredoc\n", 127);*/
		return (NULL);
	}
	redir->s_heredoc.read = r_fd;
	close(w_fd);
	redir->s_heredoc.write = w_fd;
	return (redir);
}
