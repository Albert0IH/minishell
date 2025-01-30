/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:42:48 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/30 14:47:04 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		if (!ft_strcmp(line, "\0") || !check_readline(line))
		{
			free(line);
			continue ;
		}
		if (*line)
			add_history(line);
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
