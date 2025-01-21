/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:25:15 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/21 11:26:21 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_value(char *var)
{
	char	*value;

	value = getenv(var);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

static void	handle_quotes(t_parse *state, const char *s, char *expanded)
{
	if (s[state->i] == '\'' && !state->in_double_quote)
	{
		state->in_single_quote = !state->in_single_quote;
		expanded[state->j++] = s[state->i++];
	}
	else if (s[state->i] == '"' && !state->in_single_quote)
	{
		state->in_double_quote = !state->in_double_quote;
		expanded[state->j++] = s[state->i++];
	}
}

static int	handle_dollar(t_parse *state, const char *s, char *expanded)
{
	char	var[256];
	char	*value;
	int		k;

	if (s[state->i] == '$' && !state->in_single_quote)
	{
		state->i++;
		k = 0;
		while (s[state->i] && s[state->i] != ' ' && s[state->i] != '\''
			&& s[state->i] != '"' && k < 255)
			var[k++] = s[state->i++];
		var[k] = '\0';
		value = get_env_value(var);
		if (value)
		{
			ft_strcpy(&expanded[state->j], value);
			state->j += ft_strlen(value);
			free(value);
		}
		return (1);
	}
	return (0);
}

char	*expand_env_vars(const char *s)
{
	char	*expanded;
	t_parse	*state;

	expanded = malloc(1024);
	if (!expanded)
		return (free(expanded), NULL);
	state = malloc(sizeof(t_parse));
	state->i = 0;
	state->j = 0;
	state->in_single_quote = 0;
	state->in_double_quote = 0;
	while (s[state->i])
	{
		handle_quotes(state, s, expanded);
		if (handle_dollar(state, s, expanded))
			continue ;
		if (state->j < 1024 - 1)
		expanded[state->j++] = s[state->i++];
		if (state->j >= 1024)
			expanded = realloc(expanded, state->j + 1024);
	}
	expanded[state->j] = '\0';
	free(state);
	return (expanded);
}
