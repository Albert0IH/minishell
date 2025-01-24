/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:25:15 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/24 17:18:52 by ahamuyel         ###   ########.fr       */
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
		return (NULL);
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

void	tokenize_line(char *line, char **input, char **environ)
{
	int		i;
	char	*expanded;
	char	*word;
	t_parse	state;

	line[ft_strcspn(line, "\n")] = '\0';
	expanded = ft_strtok(line, " ", &state);
	if (!expanded)
		return ;
	i = 0;
	while (expanded)
	{
		word = extract_word(&state, expanded, environ);
		if (word)
			input[i++] = word;
		expanded = ft_strtok(NULL, " ", &state);
	}
	input[i] = NULL;
	if (is_operator(input[0]))
		sort_lexic(input); // printf("sort lexic\n");
}

// void	print_expandeds(char **expandeds)
// {
// 	int	i;

// 	i = 0;
// 	while (expandeds[i])
// 	{
// 		printf("expanded %d: %s\n", i, expandeds[i]);
// 		free(expandeds[i]);
// 		i++;
// 	}
// }
