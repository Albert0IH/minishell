/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:38:05 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/16 09:15:07 by ahamuyel         ###   ########.fr       */
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

char *ft_strncpy(char *dest, const char *src, size_t n) {
    size_t i;

    i = 0;
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    while (i < n) {
        dest[i] = '\0';
        i++;
    }
    return dest;
}


void	init_path(t_path *path_info)
{
	path_info->full_path = (char *)malloc(sizeof(char) + 1);
	path_info->directories = (char **)malloc(sizeof(char *) + 1);
	path_info->environ = NULL;
}

char	*get_env_value(const char *var_name, char **environ)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = ft_strlen(var_name);
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], var_name, var_len)
			&& environ[i][var_len] == '=')
			return (&environ[i][var_len + 1]);
		i++;
	}
	return (NULL);
}

char	*expand_variable(char *s, char **environ)
{
	int		s_len;
	char	*expanded;
	char	*start;
	char	*end;
	int		i;
	int		j;
	int		var_len;
	char	*var_name;
	char	*var_value;
	int		k;

	s_len = ft_strlen(s);
	expanded = malloc(s_len + 1);
	if (!expanded)
		exit(EXIT_FAILURE);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			start = &s[i + 1];
			end = start;
			while (*end && ((*end >= 'a' && *end <= 'z') || (*end >= 'A'
						&& *end <= 'Z') || (*end >= '0' && *end <= '9')
					|| *end == '_'))
				end++;
			var_len = end - start;
			var_name = malloc(var_len + 1);
			ft_strncpy(var_name, start, var_len + 1);
			var_name[var_len] = '\0';
			var_value = get_env_value(var_name, environ);
			if (var_value)
			{
				k = 0;
				while (var_value[k])
					expanded[j++] = var_name[k++];
			}
			else
			{
				k = 0;
				while (var_name[k])
					expanded[j++] = var_name[k++];
			}
			free(var_name);
			i = end - s;
		}
		else
			expanded[j++] = s[i++];
	}
	expanded[j] = '\0';
	return (expanded);
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

	expand_variable(line, environ);
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
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
	//free(line);
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
