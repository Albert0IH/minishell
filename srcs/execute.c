/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:38:05 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/16 18:55:19 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

void	init_path(t_path *path_info)
{
	path_info->full_path = (char *)malloc(sizeof(char) + 1);
	path_info->directories = (char **)malloc(sizeof(char *) + 1);
	path_info->environ = NULL;
}

char	*get_command_path(char *cmd, t_path *path_info)
{
	char	*path;
	char	*dir;
	char	*tmp;
	int		i;

	i = 0;
	path = getenv("PATH");
	if (!path)
		return (NULL);
	if (cmd[0] == '/')
		return (cmd);
	path_info->directories = ft_split(path, ':');
	while (path_info->directories[i])
	{
		dir = path_info->directories[i];
		tmp = ft_strjoin(dir, "/");
		path_info->full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(path_info->full_path, F_OK))
		{
			free_args(path_info->directories);
			return (path_info->full_path);
		}
		free(path_info->full_path);
		i++;
	}
	free_args(path_info->directories);
	return (NULL);
}

void	execute_command(char *line, char **environ)
{
	char	*commands[100];
	int		saved_stdin;
	int		saved_stdout;
	pid_t	pid;
	int		status;

	status = 0;
	line = expand_variable(line, environ, status);
	tokenize_line(line, commands);
	if (handle_redir(commands, &saved_stdout, &saved_stdin) < 0)
		return ;
	if (is_builtin(commands[0]))
		execute_builtin(commands, environ);
	else
	{
		pid = fork();
		if (!pid)
		{
			execute_from_path(commands, environ);
			exit(0);
		}
		else if (pid > 0)
			waitpid(pid, &status, 0);
	}
	free_tokens(commands);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

void	execute_from_path(char **commands, char **environ)
{
	t_path	*path;
	pid_t	pid;
	char	*cmd_path;
	int		status;

	path = malloc(sizeof(path));
	init_path(path);
	pid = fork();
	if (!pid)
	{
		cmd_path = get_command_path(commands[0], path);
		if (execve(cmd_path, commands, environ) == -1)
		{
			ft_putstr_fd("execve error\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		exit(EXIT_FAILURE);
}

void	execute(char **commands, char **environ)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	int		i;

	i = 0;
	prev_fd = 0;
	if (!commands[1])
		execute_command(commands[i], environ);
	else
	{
		while (commands[i])
		{
			if (!commands[0])
				continue ;
			if (commands[i + 1] && pipe(fd) == -1)
				exit(EXIT_FAILURE);
			pid = fork();
			if (pid == 0)
			{
				if (prev_fd)
				{
					dup2(prev_fd, STDIN_FILENO);
					close(prev_fd);
				}
				if (commands[i + 1])
				{
					close(fd[0]);
					dup2(fd[1], STDOUT_FILENO);
					close(fd[1]);
				}
				execute_command(commands[i], environ);
				exit(EXIT_FAILURE);
			}
			if (commands[i + 1])
				close(fd[1]);
			if (prev_fd)
				close(prev_fd);
			prev_fd = fd[0];
			i++;
		}
		if (prev_fd)
			close(prev_fd);
		while (wait(NULL) > 0)
			;
	}
}
