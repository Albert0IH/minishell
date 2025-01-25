/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinis <adinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:26:06 by adinis            #+#    #+#             */
/*   Updated: 2025/01/25 11:53:45 by adinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		printf("Token %d: %s\n", i, tokens[i]);
		free(tokens[i]);
		i++;
	}
}

int	check_readline(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (0);
	return (1);
}

char	**ft_environ(char **environ)
{
	char	**env;
	int		i;
	int		len;

	env = malloc(sizeof(char *) * (count_lines(environ) + 1));
	i = 0;
	while (environ[i])
	{
		len = strlen(environ[i]);
		env[i] = malloc(sizeof(char) * (len + 1));
		strcpy(env[i], environ[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

int	main(int ac, char **av, char **environ)
{
	char	*line;
	char	**commands;
	char	**env;

	(void)av;
	(void)ac;
	env = ft_environ(environ);
	setup_signals();
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			rl_clear_history();
			free_args(commands);
			free(line);
			printf("exit\n");
			break ;
		}
		if (!ft_strcmp(line, "\0") || !check_readline(line))
		{
			free(line);
			continue ;
		}
		if (*line)
			add_history(line);
		commands = split_commands(line);
		execute(commands, env);
		free_args(commands);
	}
	free(line);
	free_args(env);
	return (0);
}
