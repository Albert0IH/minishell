/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:09:09 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/27 12:16:23 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char **args)
{
	if (strcmp(args[0], "cd") == 0)
		return (builtin_cd(args), 1);
	if (strcmp(args[0], "echo") == 0)
		return (builtin_echo(args), 1);
	if (strcmp(args[0], "exit") == 0)
		return (builtin_exit(), 1);
	if (strcmp(args[0], "env") == 0)
		return (builtin_env(), 1);
	return (0);
}

int	builtin_cd(char **args)
{
	if (!args[1])
		fprintf(stderr, "minishell: cd: expected argument\n");
	else if (chdir(args[1]) != 0)
		perror("minishell");
	return (0);
}

int	builtin_echo(char **args)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (args[i] && strcmp(args[i], "-n") == 0)
	{
		new_line = 1;
		new_line = 0, i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}

int	builtin_exit(void)
{
	printf("minishell: exiting...\n");
	exit(0);
}

int	builtin_env(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
		printf("%s\n", environ[i++]);
	return (0);
}
