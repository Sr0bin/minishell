/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:45:01 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 15:36:35 by rorollin         ###   ########.fr       */
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
	if (temp_path == NULL)
		return (NULL);
	fd_ascii = ft_itoa(fd);
	if (fd_ascii == NULL)
	{
		free(temp_path);
		return (NULL);
	}
	temp_path = ft_strcat(&temp_path, fd_ascii);
	return (temp_path);
}

static t_redir	*heredoc_create_redir(int r_fd)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (redir == NULL)
		return (NULL);
	redir->type = REDIR_HEREDOC;
	redir->s_heredoc.read = r_fd;
	return (redir);
}

static int	heredoc_create_read(int w_fd)
{
	int		r_fd;
	char	*temp_path;

	temp_path = temp_folder_path(w_fd);
	if (temp_path == NULL)
	{
		close(w_fd);
		return (-1);
	}
	r_fd = open(temp_path, O_RDONLY);
	free(temp_path);
	if (r_fd < 0)
	{
		close(w_fd);
		ft_error("Can't read temp file for Heredoc\n", 127);
		return (-1);
	}
	return (r_fd);
}

t_redir	*heredoc_create_fd(t_token_list *eof_token)
{
	t_redir	*redir;
	char	*eof_string;
	int		w_fd;
	int		r_fd;

	if (eof_token == NULL || eof_token->next == NULL)
	{
		ft_error("Heredoc : syntax error", 127);
		return (NULL);
	}
	eof_string = lst_to_tkn(eof_token->next)->content;
	w_fd = open("/tmp", O_TMPFILE | O_WRONLY, 0600);
	if (w_fd < 0)
		return (NULL);
	prompt_heredoc(w_fd, eof_string);
	r_fd = heredoc_create_read(w_fd);
	if (r_fd == -1)
		return (NULL);
	redir = heredoc_create_redir(r_fd);
	if (redir == NULL)
		return (NULL);
	close(w_fd);
	return (redir);
}
