/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:51:42 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/27 14:29:04 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char	*find_exec(char *command)
{
	char	*path_env;
	char	*path;
	char	full_path[1024];

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	path = ft_strtok(path_env, ":");
	while (path)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", path, command);
		if (access(full_path, X_OK) == 0)
			return (ft_strdup(full_path));
		path = ft_strtok(NULL, ":");
	}
	return (NULL);
}

void	exec_command(char **args)
{
	pid_t	pid;
	int		status;
	char	*full_path = find_exec(args[0]);

	if (!full_path)
	{
		fprintf(stderr, "minishell: command not found: %s\n", args[0]);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(full_path, args, NULL) == -1)
			perror("minishell");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("minishell");
	free(full_path);
}
