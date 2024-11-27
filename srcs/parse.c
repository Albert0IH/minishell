/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:51:33 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/27 11:47:30 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_delim(char c, const char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

int	count_tokens(const char *input)
{
	int	count = 0;
	int	in_token = 0;

	while (*input)
	{
		if ((*input != ' ' && *input != '\t') && !in_token)
		{
			in_token = 1;
			count++;
		}
		else if (*input == ' ' || *input == '\t')
			in_token = 0;
		input++;
	}
	return (count);
}


char	*ft_strtok(char *s, const char *delim)
{
	static char	*save_ptr;
	char		*token;

	if (s)
		save_ptr = s;
	if (!save_ptr)
		return (NULL);
	while (*save_ptr && is_delim(*save_ptr, delim))
		save_ptr++;
	if (!*save_ptr)
		return (NULL);
	token = save_ptr;
	while (*save_ptr && !is_delim(*save_ptr, delim))
		save_ptr++;
	if (*save_ptr)
		*save_ptr++ = '\0';
	return (token);
}

char	**tokenize(char *input)
{
	char	**tokens;
	char	*token;
	int		i = 0;
	int		token_count = count_tokens(input);

	tokens = malloc((token_count + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	token = ft_strtok(input, " \t");
	while (token)
	{
		tokens[i++] = ft_strdup(token);
		token = ft_strtok(NULL, " \t");
	}
	tokens[i] = NULL;
	return (tokens);
}

void	free_tokens(char **tokens)
{
	int	i = 0;

	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}
