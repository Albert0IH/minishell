/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinis <adinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:38:05 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/12/21 15:40:48 by adinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_args(char **args)
{
	int i;

	i = 0;
	if (args)
	{
		while (args[i])
			free(args[i++]);
		free(args);
	}
}

void init_path(t_path *path_info)
{
	path_info->full_path = (char *)malloc(sizeof(char) + 1);
	path_info->directories = (char **)malloc(sizeof(char *) + 1);;
	path_info->environ = NULL;
}

char *get_command_path(char *cmd, t_path *path_info)
{
	char *path;
	char *dir;
	char *tmp;
	int i;

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

void exec_command(char *cmd)
{
	t_path *path_info;
	char *args[100];
	int status;
	pid_t pid;
	char *cmd_path;
	int saved_stdout;
	int saved_stdin;

	/*
	----- saved_stds para guardar os descritores de saida e entrada.
	-- assim o prompt nao fica preso no processo criado apos '>'
	-- e volta para o terminal
	*/
	path_info = malloc(sizeof(t_path));
	init_path(path_info);
	tokenize_line(cmd, args);
	cmd_path = get_command_path(cmd, path_info);
	pid = fork();
	if (pid == 0)
	{
		if (is_builtin(args[0]))
		{
			if (handle_redir(args, &saved_stdout, &saved_stdin))
			{
				ft_putstr_fd("ERROR: Redirection error\n", STDERR_FILENO);
				return ;
			}
			exec_builtin(args);
			dup2(saved_stdout, STDOUT_FILENO);
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdout);
			close(saved_stdin);
		}
		else
		{
			if (handle_redir(args, &saved_stdout, &saved_stdin))
				return(ft_putstr_fd("ERROR: Redirection error\n", STDERR_FILENO));
			if (execve(cmd_path, args, path_info->environ))
				ft_putstr_fd("ERROR: execve\n", STDERR_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdout);
			close(saved_stdin);
		}
	}
	waitpid(pid, &status, 0);
}
