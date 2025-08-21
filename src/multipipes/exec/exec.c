/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:08:44 by lserodon          #+#    #+#             */
/*   Updated: 2025/08/21 21:05:29 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes/multipipes.h"

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
		if (fd < 0)
			return (-1);
		if (redir->type == REDIR_INPUT)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close (fd);
		node = node->next;
	}
	return (0);
}
 /* 
int		exec_builtin(t_cmds *cmd)
{
	if (ft_strcmp(cmd->cmd, "cd"))
		return (ft_cd(cmd));
	else if (ft_strcmp (cmd->cmd[0], "echo"))
		return (ft_echo(cmd));
	else if (ft_strcmp (cmd->cmd, "env"))
		return (ft_env);
	else if (ft_strcmp(cmd->cmd, "export"))
		return (ft_export);
	else if (ft_strcmp(cmd->cmd, "pwd"))
		return (ft_pwd());
	else if (ft_strcmp(cmd->cmd, "unset"))
		return (ft_unset);
	return (-1);
}  */

void exec_cmd(t_exec_data *exec_data, int i)
{
	int j;
	if (apply_redirections(exec_data, i) < 0)
		ft_error(exec_data, "minishell: no such file or directory", 1);
	if (i > 0)
		dup2(exec_data->fd[i - 1][0], STDIN_FILENO);
	if (i < exec_data->nb_cmds - 1)
		dup2(exec_data->fd[i][1], STDOUT_FILENO);
	j = 0;
	while (j < exec_data->nb_cmds - 1)
 	{
		if (j != i - 1 && exec_data->fd[j][0] >= 0)
			close(exec_data->fd[j][0]);
		if (j != i && exec_data->fd[j][1] >= 0)
			close(exec_data->fd[j][1]);
		j++;
 	}
	exec_data->cmds[i].path = find_path(exec_data, i);
	if (!exec_data->cmds[i].path)
		ft_error(exec_data, "minishell: command not found", 127);
	if (execve(exec_data->cmds[i].path, exec_data->cmds[i].cmd,
		exec_data->envp) == -1)
		ft_error(exec_data, "minishell: execve failed", 1);
}

void	close_parent_fds(t_exec_data *exec_data, int i)
{
	if (i > 0)
		close(exec_data->fd[i-1][0]);
	if (i < exec_data->nb_cmds - 1)
		close(exec_data->fd[i][1]);
}

void	exec_pipex(t_exec_data *exec_data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < exec_data->nb_cmds)
	{
		if (i < exec_data->nb_cmds - 1)
		{
			if (pipe(exec_data->fd[i]) == -1)
    			ft_error(exec_data, "minishell: pipe failed", 1);
		}
		pid = fork();
		if (pid == -1)
			ft_error(exec_data, "minishell: fork failed", 1);
		else if (pid == 0)
			exec_cmd(exec_data, i);
		else
			close_parent_fds(exec_data, i);
		i++;
	}
	i = 0;
	while (i < exec_data->nb_cmds)
	{
		wait(NULL);
		i++;
	}
	free_exec_data(exec_data);
}

