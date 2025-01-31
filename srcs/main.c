/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:42:48 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/31 16:17:50 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_status = 0;

void	execute_on_main(char *line, char **env, t_path *path)
{
	char	**commands;
	path->status = 0;
	commands = malloc(sizeof(char *) * (count_commands(line) + 1));
	if (g_status == 130)
	{
		chang_exit_status(env, ft_itoa(g_status));
		g_status = 0;
		path->status = 0;
	}
	else
	{
		chang_exit_status(env, ft_itoa(path->status));
		path->status = 0;
	}
	execute(line, commands, env, path);
	// chang_exit_status(env, ft_itoa(path->status));
	free(commands);
	commands = NULL;
	free(line);
	line = NULL;
}

void	main_loop(char **env, t_path *path)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			free(line);
			break ;
		}
		if (*line)
			add_history(line);
		if (!ft_strcmp(line, "\0") || !check_readline(line))
		{
			free(line);
			continue ;
		}
		execute_on_main(line, env, path);
	}
}

int	main(int ac, char **av, char **environ)
{
	char	**env;
	t_path	*path;

	path = malloc(sizeof(t_path));
	init_path(path);
	(void)ac;
	(void)av;
	env = ft_environ(environ);
	setup_signals();
	main_loop(env, path);
	rl_clear_history();
	free_args(env);
	free(path);
	return (0);
}
