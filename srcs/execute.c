/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:56:37 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/02/04 14:59:40 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_from_path(char **commands, char ***environ, t_path *path)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		if (execve(path->cmd_path, commands, *environ) == -1)
			exit(2);
	}
	else if (pid > 0)
	{
		signal(SIGINT, handle_sig_on_cat);
		waitpid(pid, &path->status, 0);
		signal(SIGINT, handle_signal);
	}
	else
		exit(2);
}

void	exec(char **commands, char ***environ, t_path *path)
{
	if (is_builtin(commands[0]))
	{
		path->status = 0;
		chang_exit_status(*environ, ft_itoa(path->status));
		execute_builtin(commands, environ, path);
	}
	else
	{
		path->cmd_path = get_command_path(commands[0], path, *environ);
		if (!path->cmd_path)
		{
			msg_from_path(commands[0], path);
			path->status = 127;
			chang_exit_status(*environ, ft_itoa(path->status));
			free_args(commands);
			return ;
		}
		execute_from_path(commands, environ, path);
		free(path->cmd_path);
	}
	free_args(commands);
}

void	execute_command(char *line, char **commands, char ***environ,
		t_path *path)
{
	int	saved_stdin;
	int	saved_stdout;

	commands = tokenize_line(line, *environ);
	if (handle_redir(commands, &saved_stdout, &saved_stdin) < 0)
	{
		free_args(commands);
		return ;
	}
	exec(commands, environ, path);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

void	execute(char *line, char **commands, char ***environ, t_path *path)
{
	split_commands(line, commands);
	if (!commands[1])
		execute_command(commands[0], commands, environ, path);
	else
		exec_multi_commands(commands, environ, path);
}
