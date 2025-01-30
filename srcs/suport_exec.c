/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suport_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:25:57 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/30 14:30:10 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	msg_from_path(char *command, t_path *path)
{
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("command not found\n", STDERR_FILENO);
	path->status = 127;
}

void	prepare_process(int prev_fd, char **commands, int fd[2], int i)
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
}

void	close_process(int prev_fd)
{
	if (prev_fd)
		close(prev_fd);
	while (wait(NULL) > 0)
		;
}

void	exec_multi_commands(char **commands, char **environ, t_path *path)
{
	t_process	*process;

	process = malloc(sizeof(t_process));
	init_process(process);
	while (commands[process->i])
	{
		if (commands[process->i + 1] && pipe(process->fd) == -1)
			exit(1);
		process->pid = fork();
		if (process->pid == 0)
		{
			prepare_process(process->prev_fd, commands, process->fd,
				process->i);
			execute_command(commands[process->i], commands, environ, path);
			exit(1);
		}
		if (commands[process->i + 1])
			close(process->fd[1]);
		if (process->prev_fd)
			close(process->prev_fd);
		process->prev_fd = process->fd[0];
		process->i++;
	}
	close_process(process->prev_fd);
	free(process);
}
