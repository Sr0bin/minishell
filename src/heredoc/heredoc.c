/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:45:01 by rorollin          #+#    #+#             */
/*   Updated: 2025/09/22 09:52:31 by rorollin         ###   ########.fr       */
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

t_redir	*heredoc_create_fd(t_token_list *eof_token)
{
	t_redir	*redir;
	char	*temp_path;
	char	*eof_string;
	int		w_fd;
	int		r_fd;

	if (eof_token == NULL || eof_token->next == NULL)
	{
		ft_error("Heredoc : syntax error", 127);
		return (NULL);
	}
	redir = ft_calloc(1, sizeof(t_redir));
	if (redir == NULL)
		return (NULL);
	redir->type = REDIR_HEREDOC;
	eof_string = lst_to_tkn(eof_token->next)->content;
	w_fd = open("/tmp", O_TMPFILE | O_WRONLY, 0600);
	if (w_fd < 0)
	{
		ft_error("Can't open temp file for Heredoc\n", 127);
		return (NULL);
	}
	prompt_heredoc(w_fd, eof_string);
	temp_path = temp_folder_path(w_fd);
	if (temp_path == NULL)
	{
		free(redir);
		close(w_fd);
		return (NULL);
	}
	r_fd = open(temp_path, O_RDONLY);
	free(temp_path);
	if (r_fd < 0)
	{
		close(w_fd);
		ft_error("Can't read temp file for Heredoc\n", 127);
		return (NULL);
	}
	redir->s_heredoc.read = r_fd;
	close(w_fd);
	return (redir);
}
