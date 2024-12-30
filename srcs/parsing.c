#include "../includes/minishell.h"

char	*my_strtok(char *str, const char *delim)
{
	char		*start;
	static char	*current = NULL;
	int			in_single_quote = 0;
	int			in_double_quote = 0;

	if (str != NULL)
		current = str;
	if (current == NULL)
		return (NULL);

	// Ignorar delimitadores iniciais
	while (*current && ft_strchr(delim, *current) && !in_single_quote && !in_double_quote)
		current++;

	if (*current == '\0')
		return (NULL);

	// Marcar início do token
	start = current;

	// Avançar até encontrar um delimitador fora de aspas
	while (*current)
	{
		if (*current == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote; // Alternar estado de aspas simples
		else if (*current == '"' && !in_single_quote)
			in_double_quote = !in_double_quote; // Alternar estado de aspas duplas
		else if (ft_strchr(delim, *current) && !in_single_quote && !in_double_quote)
			break;
		current++;
	}

	// Finalizar o token
	if (*current)
	{
		*current = '\0';
		current++;
	}

	return (start);
}

char	*extract_quote(char *token)
{
	char	*word;
	int		i, j;
	int		in_single_quote = 0;
	int		in_double_quote = 0;

	if (!token)
		return (NULL);

	word = malloc(ft_strlen(token) + 1);
	if (!word)
		return (NULL);

	i = 0;
	j = 0;

	while (token[i])
	{
		if (token[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote; // Alternar estado de aspas simples
			i++;
			continue;
		}
		else if (token[i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote; // Alternar estado de aspas duplas
			i++;
			continue;
		}
		word[j++] = token[i++];
	}
	word[j] = '\0';
	return (word);
}

void	tokenize_inputs(char *input, char **args)
{
	int		i;
	char	*token;
	char	*word;

	input[ft_strcspn(input, "\n")] = '\0'; // Remover newline no final do input

	token = my_strtok(input, " ;");
	i = 0;
	while (token != NULL)
	{
		word = extract_quote(token); // Remover aspas, preservando conteúdo
		if (word)
			args[i++] = word;
		token = my_strtok(NULL, " ;");
	}
	args[i] = NULL; // Finalizar o array de argumentos
}
