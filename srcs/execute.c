/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:38:05 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/10 16:59:42 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
			free(args[i++]);
		free(args);
	}
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

void	exec_command(char *cmd)
{
	t_path	*path_info;
	char	*args[100];
	char	*cmd_path;
	int		saved_stdin;
	int		saved_stdout;

	path_info = malloc(sizeof(path_info));
	init_path(path_info);
	tokenize_line(cmd, args);
	if (handle_redir(args, &saved_stdout, &saved_stdin) < 0)
		return (ft_putstr_fd("Redir error\n", STDERR_FILENO));
	if (is_builtin(args[0]))
	{
		exec_builtin(args);
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDERR_FILENO);
		close(saved_stdout);
		close(saved_stdin);
		return ;
	}
	cmd_path = get_command_path(args[0], path_info);
	if (!cmd_path)
	{
		ft_putstr_fd("Command not found\n", STDERR_FILENO);
		return ;
	}
	if (execve(cmd_path, args, environ) == -1)
	{
		ft_putstr_fd("execve error\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	execute(char **commands)
{
	pid_t	pid;
	int		status;
	int		fd[2];
	int		in_fd;
	int		i;

	i = 0;
	while (commands[i])
	{
		if (commands[i + 1] && pipe(fd) == -1)
		{
			ft_putstr_fd("Error: pipe\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (!pid)
		{
			if (in_fd)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (commands[i + 1])
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			close(fd[0]);
			exec_command(commands[i]);
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (in_fd)
				close(in_fd);
			if (commands[i + 1])
				in_fd = fd[0];
			close(fd[1]);
		}
		i++;
	}
}
