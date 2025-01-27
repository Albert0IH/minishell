/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:38:05 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/27 19:46:37 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_from_path(char **commands, char **environ)
{
	t_path	*path;
	pid_t	pid;
	char	*cmd_path;
	int		status;

	path = malloc(sizeof(t_path));
	init_path(path);
	pid = fork();
	if (!pid)
	{
		cmd_path = get_command_path(commands[0], path, environ);
		if (execve(cmd_path, commands, environ) == -1)
		{
			ft_putstr_fd(commands[0], STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd("command not found\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		exit(EXIT_FAILURE);
	free(path);
}

void	execute_command(char *line, char **environ)
{
	char	**commands;
	// int		saved_stdin;
	// int		saved_stdout;

	commands = tokenize_line(line, environ);
	// if (handle_redir(commands, &saved_stdout, &saved_stdin) < 0)
	// {
	// 	free_args(commands);
	// 	return ;
	// }
	if (is_builtin(commands[0]))
		execute_builtin(commands, environ);
	else
	execute_from_path(commands, environ);
	// dup2(saved_stdout, STDOUT_FILENO);
	// dup2(saved_stdin, STDIN_FILENO);
	// close(saved_stdout);
	// close(saved_stdin);
	free_args(commands);
}

// void	execute(char **commands, char **environ)
// {
// 	int		fd[2];
// 	int		prev_fd;
// 	pid_t	pid;
// 	int		i;

// 	i = 0;
// 	prev_fd = 0;
// 	if (!commands[1])
// 		execute_command(commands[i], environ);
// 	else
// 	{
// 		while (commands[i])
// 		{
// 			if (!commands[0])
// 				continue ;
// 			if (commands[i + 1] && pipe(fd) == -1)
// 				exit(EXIT_FAILURE);
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				if (prev_fd)
// 				{
// 					dup2(prev_fd, STDIN_FILENO);
// 					close(prev_fd);
// 				}
// 				if (commands[i + 1])
// 				{
// 					close(fd[0]);
// 					dup2(fd[1], STDOUT_FILENO);
// 					close(fd[1]);
// 				}
// 				execute_command(commands[i], environ);
// 				exit(EXIT_FAILURE);
// 			}
// 			if (commands[i + 1])
// 				close(fd[1]);
// 			if (prev_fd)
// 				close(prev_fd);
// 			prev_fd = fd[0];
// 			i++;
// 		}
// 		if (prev_fd)
// 			close(prev_fd);
// 		while (wait(NULL) > 0)
// 			;
// 	}
// }
