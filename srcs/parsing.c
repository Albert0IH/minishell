/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:25:15 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/16 18:15:56 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_word(char *token)
{
	char	*word;
	int		i;
	int		j;
	int		in_single_quote;
	int		in_double_quote;

	word = malloc(ft_strlen(token) + 1);
	if (!word)
		return (NULL);
	i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (token[i])
	{
		if (token[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (token[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else
			word[j++] = token[i];
		i++;
	}
	word[j] = '\0';
	return (word);
}

void	tokenize_line(char *line, char **input)
{
	int			i;
	char		*token;
	char		*word;
	t_tokenizer	state;

	line[ft_strcspn(line, "\n")] = '\0';
	token = ft_strtok(line, " ", &state);
	if (!token)
		return ;
	i = 0;
	while (token)
	{
		word = extract_word(token);
		if (word)
			input[i++] = word;
		token = ft_strtok(NULL, " ", &state);
	}
	input[i] = NULL;
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
