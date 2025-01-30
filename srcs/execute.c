/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:56:37 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/30 08:53:14 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sig_on_cat(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
}


void msg_from_path(char *command, t_path *path)
{
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("command not found\n", STDERR_FILENO);
	path->status = 127;
}

void	execute_from_path(char **commands, char **environ, t_path *path)
{
	pid_t	pid;
	char	*cmd_path;
	pid = fork();
	if (!pid)
	{
		cmd_path = get_command_path(commands[0], path, environ);
		if (!cmd_path)
			msg_from_path(commands[0], path);
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

void setup_redirections(int prev_fd, int *fd, int has_next)
{
    if (prev_fd)
    {
        dup2(prev_fd, STDIN_FILENO);
        close(prev_fd);
    }
    if (has_next)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
    }
}

void fork_and_execute(int prev_fd, int *fd, char **cmds, char **env, t_path *path, int i)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        setup_redirections(prev_fd, fd, cmds[i + 1] != NULL);
        execute_command(cmds[i], cmds, env, path);
        exit(1);
    }
}

void execute_piped_commands(char **cmds, char **env, t_path *path)
{
    int fd[2], prev_fd = 0, i = 0;
    
    while (cmds[i])
    {
        if (!cmds[i])
            continue;
        if (cmds[i + 1] && pipe(fd) == -1)
            exit(1);
        
        fork_and_execute(prev_fd, fd, cmds, env, path, i);
        
        if (cmds[i + 1])
            close(fd[1]);
        if (prev_fd)
            close(prev_fd);
        prev_fd = fd[0];
        i++;
    }
    if (prev_fd)
        close(prev_fd);
    while (wait(NULL) > 0);
}

void execute(char *line, char **cmds, char **env, t_path *path)
{
    split_commands(line, cmds);
    if (!cmds[1])
        execute_command(cmds[0], cmds, env, path);
    else
        execute_piped_commands(cmds, env, path);
}

