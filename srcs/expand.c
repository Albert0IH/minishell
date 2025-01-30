/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:31:02 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/30 09:52:22 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_value(char *var, char **environ)
{
	char	*value;

	value = ft_get_env(var, environ);
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

static int	handle_dollar(t_parse *state, const char *s, char *expanded,
		char **environ)
{
	char	var[256];
	char	*value;
	int		k;

	if (s && s[state->i] == '$' && !state->in_single_quote)
	{
		state->i++;
		k = 0;
		while (s[state->i] && s[state->i] != ' ' && s[state->i] != '\''
			&& s[state->i] != '"' && k < 255)
			var[k++] = s[state->i++];
		var[k] = '\0';
		value = get_env_value(var, environ);
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

static void	process_token(const char *s, char *expanded, t_parse *state,
		char **environ)
{
	int	len;

	len = ft_strlen(s);
	while (1)
	{
		if (state->i >= len)
			break ;
		handle_quotes(state, s, expanded);
		if (handle_dollar(state, s, expanded, environ))
			continue ;
		if (state->j < SIZE_EXPANDED - 1)
			expanded[state->j++] = s[state->i++];
		else
			break ;
	}
}

char	*expand_env_vars(const char *s, char **environ)
{
	char	*expanded;
	t_parse	*state;

	expanded = malloc(SIZE_EXPANDED);
	if (!expanded)
		return (free(expanded), NULL);
	state = malloc(sizeof(t_parse));
	init_state(state);
	process_token(s, expanded, state, environ);
	expanded[state->j] = '\0';
	free(state);
	return (expanded);
}
