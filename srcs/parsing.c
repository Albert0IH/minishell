/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:25:15 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/18 08:45:03 by ahamuyel         ###   ########.fr       */
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

	token = expand_env_vars(token);
	if (!token)
		return (NULL);
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
	free(token);
	return (word);
}

int	is_operator(char *operator)
{
	if (!ft_strcmp(operator, ">"))
		return (1);
	else if (!ft_strcmp(operator, ">>"))
		return (1);
	else if (!ft_strcmp(operator, "<"))
		return (1);
	else if (!ft_strcmp(operator, "<<"))
		return (1);
	else
		return (0);
}

void	switch_token(char **token)
{
	char *cmd = token[2];
	char *operator= token[0];
	char *file = token[1];
	
	token[0] = cmd;
	token[1] = operator;
	token[2] = file;
}
void	lexic_tokken(char **token)
{
	char	*operator= token[1];
	if (!is_operator(operator))
		switch_token(token);
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
	lexic_tokken(input);
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
