/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:14:56 by lserodon          #+#    #+#             */
/*   Updated: 2025/05/13 14:33:10 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_all(t_utils *utils)
{
	if (utils->cmd1)
		free_array(utils->cmd1);
	if (utils->cmd2)
		free_array(utils->cmd2);
	if (utils->path_cmd1)
		free(utils->path_cmd1);
	if (utils->path_cmd2)
		free(utils->path_cmd2);
}

void	free_array(char **array)
{
	int i;

	i = 0;

	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*find_path(char **envp, char *cmd)
{
	char	*path;
	char	*tmp_path;
	char	*cmd_path;
	char	**path_array;
	int		i;

	i = -1;
	while (envp && envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	}
	path_array = ft_split(path, ':');
	free (path);
	i = -1;
	while (path_array[++i])
	{
		tmp_path = ft_strjoin(path_array[i], (char *)"/");
		cmd_path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(cmd_path, X_OK) == 0)
		{
			free_array(path_array);
			return (cmd_path);
		}
		free(cmd_path);
	}
	return (NULL);
}

void	close_files(t_utils *utils)
{
	if (utils->fd[0] >= 0)
		close(utils->fd[0]);
	if (utils->fd[1] >= 0)
		close(utils->fd[1]);
	if (utils->infile >= 0)
		close(utils->infile);
	if (utils->outfile >= 0)
		close(utils->outfile);
}

void	exec_cmd1(t_utils *utils, char **envp)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		dup2(utils->infile, STDIN_FILENO);
		dup2(utils->fd[1], STDOUT_FILENO);
		close_files(utils);
		if (execve(utils->path_cmd1, utils->cmd1, envp) == -1)
		{
			free_all(utils);
			exit(1);
		}
	}
}

void	exec_cmd2(t_utils *utils, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		dup2(utils->fd[0], STDIN_FILENO);
		dup2(utils->outfile, STDOUT_FILENO);
		close_files(utils);
		if (execve(utils->path_cmd2, utils->cmd2, envp) == -1)
		{
			free_all(utils);
			exit(1);
		}
	}
}

void	inits_utils(char **argv, char **envp, t_utils *utils)
{
	utils->infile = open(argv[1], O_RDONLY);
	utils->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0655);
	pipe(utils->fd);
	utils->cmd1 = ft_split(argv[2], ' ');
	utils->cmd2 = ft_split(argv[3], ' ');
	utils->path_cmd1 = find_path(envp, utils->cmd1[0]);
	utils->path_cmd2 = find_path(envp, utils->cmd2[0]);
}

void	exec_pipex(t_utils *utils, char **envp)
{
	exec_cmd1(utils, envp);
	exec_cmd2(utils, envp);
}

int main(int argc, char **argv, char **envp)
{
	t_utils utils;
	
	(void)argc;
	inits_utils(argv, envp, &utils);
	exec_pipex(&utils, envp);
	close_files(&utils);
	free_all(&utils);
	wait (NULL);
	wait (NULL);
}
