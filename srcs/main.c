/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:42:48 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/29 06:34:49 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **environ)
{
	char	*line;
	char	**env;
	char	**commands;
	t_path	*path;

	path = malloc(sizeof(t_path));
	init_path(path);
	(void)ac;
	(void)av;
	env = ft_environ(environ);
	setup_signals();
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			free(line);
			break ;
		}
		if (!ft_strcmp(line, "\0") || !check_readline(line))
		{
			free(line);
			continue ;
		}
		if (*line)
			add_history(line);
		commands = malloc(sizeof(char *) * (count_commands(line) + 1));
		execute(line, commands, env, path);
		
		chang_exit_status(env, ft_itoa(path->status));
		printf("exit status: %d\n", path->status);
		free(commands);
		commands = NULL;
		free(line);
		line = NULL;
	}
	rl_clear_history();
	free_args(env);
	return (0);
}
