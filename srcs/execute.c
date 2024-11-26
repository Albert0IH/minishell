/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:51:42 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/26 18:15:25 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// // Função para encontrar o caminho completo do comando
// char	*find_exec(char *command)
// {
// 	char	*path_env;
// 	char	*path;
// 	char	full_path[1024];

// 	path_env = getenv("PATH");
// 	path = strtok(path_env, ":");
// 	while (path != NULL)
// 	{
// 		snprintf(full_path, sizeof(full_path), "%s/%s", path, command);
// 		if (access(full_path, X_OK) == 0)
// 		{
// 			return (strdup(full_path));
// 		}
// 		path = strtok(NULL, ":");
// 	}
// 	return (NULL);
// }

char	*find_exec(char *command)
{
	char	*path_env;
	char	*path;
	char	full_path[1024];

	path_env = getenv("PATH");
	path = ft_strtok(path_env, ":");
	while (path)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", path, command);
		// printf("%s", command);
		return (ft_strdup(full_path));
		path = ft_strtok(NULL, ";");
	}
	return (NULL);
}

// void	exec_comand(char **args)
// {
// 	pid_t	pid;
// 	int		status;
// 	char	*full_path;

// 	full_path = find_exec(args[0]);
// 	if (full_path == NULL)
// 	{
// 		fprintf(stderr, "minishell: command not found: %s\n", args[0]);
// 		return ;
// 	}
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		// Processo filho: executa o comando usando o caminho completo
// 		if (execve(full_path, args, NULL) == -1)
// 		{
// 			perror("minishell");
// 			free(full_path);
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else if (pid < 0)
// 	{
// 		perror("minishell");
// 	}
// 	else
// 	{
// 		// Processo pai: espera o processo filho terminar
// 		waitpid(pid, &status, 0);
// 	}
// 	free(full_path);
// }

void	exec_comand(char **args)
{
	pid_t	pid;
	int		status;
	char	*full_path;

	full_path = find_exec(args[0]);
	if (!full_path)
	{
        //fprintf(stderr, "minishell: comand not found: %s\n", args[0]);
		write(2, "minishell: comand not found:", 29);
		write(2, args[0], 5);
		write(2, "\n", 1);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(full_path, args, NULL) == -1)
		{
            perror("minishell");
			// write(1, "minishell\n", 10);
			// // write(2, args[0], 5);
            // free(full_path);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		write(2, "minishell\n", 10);
	else
		waitpid(pid, &status, 0);
	free(full_path);
}
