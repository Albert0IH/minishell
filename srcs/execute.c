/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:56:37 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/31 16:03:56 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_from_path(char **commands, char **environ, t_path *path)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	if (!pid)
	{
		cmd_path = get_command_path(commands[0], path, environ);
		if (execve(cmd_path, commands, environ) == -1)
		{
			msg_from_path(commands[0], path);
			exit(127);
		}
		free(cmd_path);
	}
	else if (pid > 0)
	{
		signal(SIGINT, handle_sig_on_cat);
		waitpid(pid, &path->status, 0);
		signal(SIGINT, handle_signal);
		if (WIFEXITED(path->status))
			path->status = WEXITSTATUS(path->status);
	}
	else
		exit(2);
}

void	execute_command(char *line, char **commands, char **environ,
		t_path *path)
{
	int	saved_stdin;
	int	saved_stdout;

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

void	execute(char *line, char **commands, char **environ, t_path *path)
{
	split_commands(line, commands);
	if (!commands[1])
		execute_command(commands[0], commands, environ, path);
	else
		exec_multi_commands(commands, environ, path);
}
