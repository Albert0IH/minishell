/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:30:01 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/02/03 18:32:03 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
}

int	is_operator(char *s)
{
	if (!ft_strcmp(s, ">") || !ft_strcmp(s, ">>") || !ft_strcmp(s, "<")
		|| !ft_strcmp(s, "<<"))
		return (1);
	return (0);
}

int	count_operator(char **s)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (is_operator(s[i]))
			count++;
		i++;
	}
	return (count);
}

char	*extract_word(t_parse *state, char *token, char **environ)
{
	char	*word;
	char	*expanded;

	expanded = expand_env_vars(token, environ);
	if (!expanded)
		return (NULL);
	word = malloc(ft_strlen(expanded) + 1);
	if (!word)
		return (free(expanded), NULL);
	state->i = 0;
	state->j = 0;
	while (expanded[state->i])
	{
		if (expanded[state->i] == '\'' && !state->in_double_quote)
			state->in_single_quote = !state->in_single_quote;
		else if (expanded[state->i] == '"' && !state->in_single_quote)
			state->in_double_quote = !state->in_double_quote;
		else
			word[state->j++] = expanded[state->i];
		state->i++;
	}
	free(expanded);
	word[state->j] = '\0';
	return (word);
}

char	**tokenize_line(char *line, char **environ)
{
	int		i;
	t_token	*token;
	t_parse	state;
	char	**tokens_parsed;

	token = malloc(sizeof(t_token));
	init_token(token);
	line[ft_strcspn(line, "\n")] = '\0';
	token->expanded = ft_strtok(line, " ", &state);
	if (!token->expanded)
		return (free(token->expanded), NULL);
	i = 0;
	while (token->expanded)
	{
		token->word = extract_word(&state, token->expanded, environ);
		if (token->word)
			token->tokens[i++] = token->word;
		token->expanded = ft_strtok(NULL, " ", &state);
	}
	token->tokens[i] = NULL;
	tokens_parsed = mult_lexic_sort(token->tokens);
	free_args(token->tokens);
	free(token);
	return (tokens_parsed);
}
