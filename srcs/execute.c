/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:38:05 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/13 19:06:37 by ahamuyel         ###   ########.fr       */
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

void	execute(char *line, char **environ)
{
	t_path	*path_info;
	char	*commands[100];
	char	*cmd_path;
	int		status;
	pid_t	pid;
	int		saved_stdin;
	int		saved_stdout;
	int		fd[2];
	int		i;

	path_info = malloc(sizeof(path_info));
	init_path(path_info);
	tokenize_line(line, commands);
	if (handle_redir(commands, &saved_stdout, &saved_stdin) < 0)
		return ;
	i = 0;
	while (commands[i])
	{
		if (commands[i + 1] && pipe(fd) == -1)
		{
			ft_putstr_fd("Error: pipe\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		if (is_builtin(commands[0]))
		{
			execute_builtin(commands, environ);
			dup2(saved_stdout, STDOUT_FILENO);
			dup2(saved_stdin, STDERR_FILENO);
			close(saved_stdout);
			close(saved_stdin);
		}
		else
		{
			pid = fork();
			if (!pid)
			{
				if (commands[i + 1])
					dup2(fd[1], STDOUT_FILENO);
				if (i > 0)
					dup2(fd[0], STDIN_FILENO);
				close(fd[0]);
				close(fd[1]);
				cmd_path = get_command_path(commands[0], path_info);
				if (execve(cmd_path, commands, environ) == -1)
				{
					ft_putstr_fd("execve error\n", STDERR_FILENO);
					exit(EXIT_FAILURE);
				}
			}
			else if (pid > 0)
			{
				waitpid(pid, &status, 0);
				close(fd[0]);
				close(fd[1]);
			}
		}
		i++;
	}
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDERR_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

// void	execute(char **commands, char **environ)
// {
// 	int		status;
// 	pid_t	pid;
// 	int		saved_stdin;
// 	int		saved_stdout;

// 	execute_command(commands[0], environ);
// }
