/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:51:33 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/25 15:48:23 by ahamuyel         ###   ########.fr       */
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
	if (*save_ptr == '\0')
		return (NULL);
	token = save_ptr;
	while (*save_ptr && !is_delim(*save_ptr, delim))
		save_ptr++;
	if (*save_ptr)
	{
		*save_ptr = '\0';
		save_ptr++;
	}
	return (token);
}

int	count_tokens(char *input)
{
	int		count;
	char	*token;

	count = 0;
	token = ft_strtok(input, " \t");
	while (token)
	{
		count++;
		token = ft_strtok(NULL, " \t");
	}
	return (count);
}

char	**tokenize(char *input)
{
	char	**tokens;
	char	*input_copy;
	char	*token;
	int		i;
	int		token_count;

	input_copy = ft_strdup(input);
	i = 0;
	token = NULL;
    if (!input_copy)
        return (NULL);
    token_count = count_tokens(input_copy);
    free(input_copy);
    tokens = malloc((token_count + 1) * sizeof(char *));
    if (!tokens)
        return (NULL);
    input_copy = ft_strdup(input);
    if (!input_copy)
    {
        free(input);
        return NULL;
    }
    token = ft_strtok(input_copy, " \t");
    while (token)
    {
        tokens[i++] = ft_strdup(token);
        token = ft_strtok(NULL, " \t");
    }
    tokens[i] = NULL;
    free(input_copy);
    return (tokens);
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

// int	main(void)
// {
// 	char s[] = "Este é um exemplo, de como usar; a func strtok.";
// 	char *token;
// 	token = ft_strtok(s, " .;,");
// 	while (token)
// 	{
// 		printf("%s\n", token);
// 		token = ft_strtok(NULL, " .;,");
// 	}
// 	return (0);
// }