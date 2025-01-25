/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:30:01 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/25 18:04:28 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	int i;
	t_token *token;
	t_parse state;

	token = malloc(sizeof(t_token));
	init_token(token);
	line[ft_strcspn(line, "\n")] = '\0';
	token->expanded = ft_strtok(line, " ", &state);
	if (!token->expanded)
		return (free(token->expanded), NULL);
	token->input = malloc(sizeof(char *) * 50);
	i = 0;
	while (token->expanded)
	{
		token->word = extract_word(&state, token->expanded, environ);
		if (token->word)
			token->input[i++] = token->word;
		token->expanded = ft_strtok(NULL, " ", &state);
	}
	token->input[i] = NULL;
	free(token);
	return (token->input);
}
