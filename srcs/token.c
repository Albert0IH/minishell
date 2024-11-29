/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenização.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:01:54 by adinis            #+#    #+#             */
/*   Updated: 2024/11/29 09:01:59 by adinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char	*my_strtok(char *str, const char *delim)
{
	char		*start;
	static char	*current = NULL;

	if (str != NULL)
		current = str;
	if (current == NULL)
		return (NULL);
	while (*current && strchr(delim, *current))
		current++;
	if (*current == '\0')
		return (NULL);
	start = current;
	while (*current && !strchr(delim, *current))
		current++;
	if (*current)
	{
		*current = '\0';
		current++;
	}
	return (start);
}

void	parse_input(char *input, char **args)
{
	int		i;
	char	*token;

	input[strcspn(input, "\n")] = 0;
	token = my_strtok(input, " ,&&;|/");
	i = 0;
	while (token != NULL && i < MAX_ARG_SIZE - 1)
	{
		args[i++] = token;
		token = my_strtok(NULL, " &&,;|/");
	}
	args[i] = NULL;
}

