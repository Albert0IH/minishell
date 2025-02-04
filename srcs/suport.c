/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suport.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:00:30 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/02/04 15:12:50 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		printf("Token %d: %s\n", i, tokens[i]);
		i++;
	}
}

int	count_lines(char **s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_search_str(char **array, char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (array[i])
	{
		if (!ft_strcmp(array[i], s))
			count++;
		i++;
	}
	return (count);
}

int	ft_search_on_env(char **array, char *s)
{
	int	i;
	int len;

	i = 0;
	len = 0;
	while (s[len] && s[len] != '=')
		len++;
	while (array[i])
	{
		if (!ft_strncmp(array[i], s, len))
			return (1);
		i++;
	}
	return (0);
}

int	ft_searc_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}
