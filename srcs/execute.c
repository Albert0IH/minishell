/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:56:37 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/29 06:07:15 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void son(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

void execute_from_path(char **commands, char **environ, t_path *path)
{
	pid_t pid;
	char *cmd_path;

	pid = fork();
	if (!pid)
	{
		cmd_path = get_command_path(commands[0], path, environ);
		if (!cmd_path)
		{
			ft_putstr_fd(commands[0], STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd("command not found\n", STDERR_FILENO);
			exit(127);
		}
		if (execve(cmd_path, commands, environ) == -1)
		{
			ft_putstr_fd(commands[0], STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd("execution failed\n", STDERR_FILENO);
			free(cmd_path);
			exit(127);
		}
		free(cmd_path);
	}
	else if (pid > 0)
	{
		signal(SIGINT, son);
		waitpid(pid, &path->status, 0);
		signal(SIGINT, handle_signal);
		if (WIFEXITED(path->status))
			path->status = WEXITSTATUS(path->status);
	}
	else
		exit(2);
}

void execute_command(char *line, char **commands, char **environ, t_path *path)
{
	int saved_stdin;
	int saved_stdout;

	commands = tokenize_line(line, environ);
	if (handle_redir(commands, &saved_stdout, &saved_stdin) < 0)
	{
		free_args(commands);
		return ;
	}
	if (is_builtin(commands[0]))
		execute_builtin(commands, environ, path);
	else
		execute_from_path(commands, environ, path);
	free_args(commands);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

void execute(char *line, char **commands, char **environ, t_path *path)
{
	int fd[2];
	pid_t pid;
	int i;

	int prev_fd = 0;
	i = 0;
	split_commands(line, commands);
	if (!commands[1])
		execute_command(commands[i], commands, environ, path);
	else
	{
		while (commands[i])
		{
			if (!commands[0])
				continue ;
			if (commands[i + 1] && pipe(fd) == -1)
				exit(1);
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
				execute_command(commands[i], commands, environ, path);
				exit(1);
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
