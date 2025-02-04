/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:56:37 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/02/04 11:32:20 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (is_builtin(commands[0]))
		execute_builtin(commands, environ, path);
	else
	{
		path->cmd_path = get_command_path(commands[0], path, *environ);
		if (!path->cmd_path)
		{
			msg_from_path(commands[0], path);
			path->status = 127;
			return ;
		}
		execute_from_path(commands, environ, path);
	}
	free_args(commands);
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
