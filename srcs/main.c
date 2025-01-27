/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:42:48 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/27 11:23:56 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **environ)
{
	char	*line;
	char	**commands;
	char	**env;

	(void)ac;
	(void)av;
    env = ft_environ(environ);
	setup_signals();
	while (1)
	{
		line = readline("minishell$ ");
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
		commands = tokenize_line(line, env);
		if (!commands)
		{
			free(line);
			continue ;
		}
		print_tokens(commands);
        free_args(commands);
		free(line);
	}
	rl_clear_history();
    free_args(env);
	return (0);
}
