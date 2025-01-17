/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:25:15 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/17 15:07:42 by ahamuyel         ###   ########.fr       */
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

static void	handle_quotes(const char *s, int *i, int *in_single_quote,
		int *in_double_quote, char *expanded, int *j)
{
	if (s[*i] == '\'' && !(*in_double_quote))
	{
		*in_single_quote = !(*in_single_quote);
		expanded[(*j)++] = s[(*i)++];
	}
	else if (s[*i] == '"' && !(*in_single_quote))
	{
		*in_double_quote = !(*in_double_quote);
		expanded[(*j)++] = s[(*i)++];
	}
}

static int	handle_dollar(const char *s, int *i, char *expanded, int *j,
		int in_single_quote)
{
	char	var[256];
	char	*value;
	int		k;

	if (s[*i] == '$' && !in_single_quote)
	{
		(*i)++;
		k = 0;
		while (s[*i] && s[*i] != ' ' && s[*i] != '\'' && s[*i] != '"'
			&& k < 255)
			var[k++] = s[(*i)++];
		var[k] = '\0';
		value = get_env_value(var);
		ft_strcpy(&expanded[*j], value);
		*j += ft_strlen(value);
		free(value);
		return (1);
	}
	return (0);
}

char	*expand_env_vars(const char *s)
{
	char	*expanded;
	int		i;
	int		j;
	int		in_single_quote;
	int		in_double_quote;

	expanded = malloc(1024);
	if (!expanded)
		return (NULL);
	i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (s[i])
	{
		handle_quotes(s, &i, &in_single_quote, &in_double_quote, expanded, &j);
		if (handle_dollar(s, &i, expanded, &j, in_single_quote))
			continue ;
		if (s[i])
			expanded[j++] = s[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}

