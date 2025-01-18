/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:25:15 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/18 11:01:26 by ahamuyel         ###   ########.fr       */
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
// Verifica se a string é um operador
int is_operator(const char *token) {
    return (!ft_strcmp(token, ">") || !ft_strcmp(token, ">>") ||
            !ft_strcmp(token, "<") || !ft_strcmp(token, "<<"));
}

// Encontra o índice do primeiro operador na lista de tokens
int find_first_operator(char **tokens) {
    for (int i = 0; tokens[i]; i++) {
        if (is_operator(tokens[i]))
            return i;
    }
    return -1; // Nenhum operador encontrado
}

// Reorganiza os tokens na ordem: comando -> operador -> arquivo(s)
void reorder_tokens(char **tokens) {
    int operator_index = find_first_operator(tokens);
    if (operator_index <= 0) // Sem operador ou operador já está na posição correta
        return;

    char *operator = tokens[operator_index];
    char *file = tokens[operator_index + 1];
    
    // Move comando para o início
    for (int i = operator_index; i > 0; i--) {
        tokens[i + 1] = tokens[i - 1];
    }

    // Reposiciona operador e arquivo
    tokens[1] = operator;
    tokens[2] = file;
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
	reorder_tokens(input);
}
void free_tokens(char **tokens) {
    for (int i = 0; tokens[i]; i++) {
        free(tokens[i]);
    }
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
