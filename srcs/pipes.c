/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:10:22 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/28 14:35:28 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void split_commands(char *input, char	**commands)
{
	int		i;
	char	*tokens;
	t_parse	states;

	tokens = ft_strtok(input, "|", &states);
	i = 0;
	while (tokens)
	{
		commands[i] = tokens;
		tokens = ft_strtok(NULL, "|", &states);
		i++;
	}
	commands[i] = NULL;
	//return (commands);
}

int	count_commands(char *input)
{
	int		i;
	int		count;
	t_parse	states;

	states.in_single_quote = 0;
	states.in_double_quote = 0;
	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|' && (!states.in_single_quote
				|| !states.in_double_quote))
			count++;
		i++;
	}
	return (count + 1);
}
