/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:25:15 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/17 11:22:56 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <string.h>

char *get_env_value(char *var)
{
	char *value;

	value = getenv(var);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

static void	handle_quotes(const char *str, int *i, int *in_single_quote,
		int *in_double_quote, char *expanded, int *j)
{
	if (str[*i] == '\'' && !(*in_double_quote))
	{
		*in_single_quote = !(*in_single_quote);
		expanded[(*j)++] = str[(*i)++];
	}
	else if (str[*i] == '"' && !(*in_single_quote))
	{
		*in_double_quote = !(*in_double_quote);
		expanded[(*j)++] = str[(*i)++];
	}
}

static int	handle_dollar(const char *str, int *i, char *expanded, int *j,
		int in_single_quote)
{
	char	var[256];
	char	*env_value;
	int		k;

	if (str[*i] == '$' && !in_single_quote)
	{
		(*i)++;
		k = 0;
		while (str[*i] && str[*i] != ' ' && str[*i] != '\'' && str[*i] != '"'
			&& k < 255)
			var[k++] = str[(*i)++];
		var[k] = '\0';
		env_value = get_env_value(var);
		strcpy(&expanded[*j], env_value);
		*j += strlen(env_value);
		free(env_value);
		return (1);
	}
	return (0);
}

char	*expand_env_vars(const char *str)
{
	char	*expanded;
	int		i;
	int		j;
	int		in_single_quote;
	int		in_double_quote;

	expanded = malloc(1024); // Buffer para a string expandida
	if (!expanded)
		return (NULL);
	i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (str[i])
	{
		handle_quotes(str, &i, &in_single_quote, &in_double_quote, expanded,
			&j);
		if (handle_dollar(str, &i, expanded, &j, in_single_quote))
			continue ;
		if (str[i])
			expanded[j++] = str[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}

char	*extract_word(char *token)
{
	char	*word;
	int		i;
	int		j;
	int		in_single_quote;
	int		in_double_quote;

	token = expand_env_vars(token);
		// Expande as variáveis de ambiente antes da extração
	if (!token)
		return (NULL);
	word = malloc(strlen(token) + 1);
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
	free(token); // Libera a string expandida original
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
