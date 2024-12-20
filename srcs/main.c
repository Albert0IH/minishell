/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:11:09 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/30 01:33:14 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*args[MAX_ARG_SIZE];
	char	*rl;

	setup_signals();
	while (1)
	{
		rl = readline("minishell> ");
		if (!rl)
		{
			printf("exit\n");
			break ;
		}
		if (*rl)
			add_history(rl);
		parse_input(rl, args);
		if (args[0] == NULL)
		{
			free(rl);
			continue ;
		}
		execute_cmd(args);
		free(rl);
	}
	return (0);
}
