/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:06:18 by lulussi           #+#    #+#             */
/*   Updated: 2025/05/10 14:15:51 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char 	**parse_cmd(char *cmd)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
	return (cmd_args);
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
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	}
	path_array = ft_split(path, ':');
	i = -1;
	while (path_array[++i])
	{
		tmp_path = ft_strjoin(path_array[i], "/");
		cmd_path = ft_strjoin(tmp_path, cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			return (cmd_path);
		}
	}
	return (NULL);
}

void	first_cmd(int infile, char **argv, char **envp, int fd[2])
{
	char *path;
	char **cmd_args;
	
	close(fd[0]);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(infile);
	cmd_args = parse_cmd(argv[2]);
	path = find_path(envp, cmd_args[0]);
	execve(path, cmd_args, envp);
} 

void	second_cmd(int outfile, char **argv, char **envp, int fd[2])
{
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]); // après dup2
	close(fd[1]); // ne l’utilise pas
	close(outfile); // après dup2
	char **cmd_args = parse_cmd(argv[3]);
	char *path = find_path(envp, cmd_args[0]);
	execve(path, cmd_args, envp);
}

int main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int infile;
	int outfile;
	pid_t pid;
	pid_t	pid2;

	if (argc != 5)
		return (1);
	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pipe(fd);
	pid = fork();
	if (pid == 0)
		first_cmd(infile, argv, envp, fd);
	pid2 = fork();
	if (pid2 == 0)
		second_cmd(outfile, argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
}
