/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:25:15 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/20 16:29:59 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_word(t_parse *state, char *token)
{
	char	*word;

	token = expand_env_vars(token);
	if (!token)
		return (NULL);
	word = malloc(ft_strlen(token) + 1);
	if (!word)
		return (NULL);
	state->i = 0;
	state->j = 0;
	while (token[state->i])
	{
		if (token[state->i] == '\'' && !state->in_double_quote)
			state->in_single_quote = !state->in_single_quote;
		else if (token[state->i] == '"' && !state->in_single_quote)
			state->in_double_quote = !state->in_double_quote;
		else
			word[state->j++] = token[state->i];
		state->i++;
	}
	word[state->j] = '\0';
	free(token);
	return (word);
}

void	tokenize_line(char *line, char **input)
{
	int			i;
	char		*token;
	char		*word;
	t_parse	state;

	line[ft_strcspn(line, "\n")] = '\0';
	token = ft_strtok(line, " ", &state);
	if (!token)
		return ;
	i = 0;
	while (token)
	{
		word = extract_word(&state, token);
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
