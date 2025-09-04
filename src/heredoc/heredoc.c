/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:45:01 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/04 15:53:08 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"
#include <fcntl.h>

#include <sys/stat.h>
#include <unistd.h>

static const char	*temp_file_path()
{
	return (".hd.tmp");
}

t_redir	heredoc_create_fd()
{
	t_redir	redir;
	char	*temp_path;
	char	*fd_ascii;
	int	w_fd;
	int	r_fd;

	redir.type = REDIR_HEREDOC;
	w_fd = open("/tmp", O_TMPFILE | O_WRONLY, 0600);
	if (w_fd < 0)
	{
		/*ft_error(exec_data_context(NULL, READ_EXEC_DATA), "Can't open temp file for Heredoc\n", 127);*/
		return ((t_redir) {0});
	}
	temp_path = ft_strdup("/proc/self/fd/");
	fd_ascii = ft_itoa(w_fd);
	temp_path = ft_strcat(&temp_path, fd_ascii);
	r_fd = open(temp_path, O_RDONLY);
	free(temp_path);
	if (r_fd < 0)
	{
		close(w_fd);
		/*ft_error(exec_data_context(NULL, READ_EXEC_DATA), "Can't read temp file for Heredoc\n", 127);*/
		return ((t_redir) {0});
	}
	redir.s_heredoc.read = r_fd;
	redir.s_heredoc.write = w_fd;
	return (redir);
}
