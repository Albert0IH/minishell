/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:56:44 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/27 16:06:48 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_matrix(char **matrix)
{
    int	i;

    i = 0;
    while (matrix[i])
        free(matrix[i++]);
}

// void free_args(char **args)
// {
//     int	i;

//     i = 0;
//     if (args)
//     {
//         while (args[i])
//             free(args[i++]);
//         free(args);
//     }
// }

// void print_tokens(char **tokens)
// {
//     int i = 0;
//     while (tokens[i])
//     {
//         printf("Token %d: %s\n", i, tokens[i]);
//         i++;
//     }
// }

int	ft_search_str(char **array, char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (array[i])
	{
		if (!strcmp(array[i], s))
			count++;
		i++;
	}
	return (count);
}

int	ft_searc_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	is_operator(char *s)
{
	if (!strcmp(s, ">") || !strcmp(s, ">>") || !strcmp(s, "<")
		|| !strcmp(s, "<<"))
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

char	**operator_matrix(char **input)
{
	int		i;
	int		j;
	char	**new_input;

	i = 0;
	j = 0;
	new_input = malloc(sizeof(char *) * ((count_operator(input) * 2) + 1));
	while (input[i])
	{
		if (is_operator(input[i]) && input[i + 1])
		{
			new_input[j] = strdup(input[i]);
			if (!new_input[j])
				return (free_args(new_input), NULL);
			new_input[j + 1] = strdup(input[i + 1]);
			i += 2;
			j += 2;
			continue ;
		}
		i++;
	}
	new_input[j] = NULL;
	return (new_input);
}

char	**sort_lexic(char **av)
{
	char	**lexic_tokens;
	char	**mop;
	int		i;
	int		j;

	lexic_tokens = malloc(sizeof(char *) * (count_lines(av) + 1));
	mop = operator_matrix(av);
	i = 0;
	j = 0;
	while (av[i])
	{
		if (is_operator(av[i]) && av[i + 1])
		{
			i += 2;
			continue ;
		}
		else
			lexic_tokens[j] = strdup(av[i]);
		i++;
		j++;
	}
	i = 0;
	while (mop[i])
		lexic_tokens[j++] = strdup(mop[i++]);
	lexic_tokens[j] = NULL;
	free_args(mop);
	return (lexic_tokens);
}

char	**matrix_join(char **mtx1, char **mtx2, int pipe)
{
	char	**matrix;
	int		i;
	int		j;
	size_t	len_m1;
	size_t	len_m2;

	i = 0;
	j = 0;
	len_m1 = count_lines(mtx1);
	len_m2 = count_lines(mtx2);
	matrix = malloc(sizeof(char *) * (len_m1 + len_m2 + 2));
	while (mtx1 && mtx1[i])
		matrix[j++] = strdup(mtx1[i++]);
	if (pipe && mtx1)
		matrix[j] = strdup("|");
	i = 0;
	while (mtx2 && mtx2[i])
		matrix[j++] = strdup(mtx2[i++]);
	matrix[j] = NULL;
	free_args(mtx1);
	return (matrix);
}

char	**mult_lexic_sort(char **input)
{
	char	**final;

	final = NULL;
	final = sort_lexic(input);
	return (final);
}

// int main(void)
// {
//     char *input;
//     char **tokens;
//     char **sorted;

//     while (1)
//     {
//         input = readline("shell> "); // Prompt para entrada do usuário
//         if (!input || strcmp(input, "exit") == 0) // Sair com "exit" ou EOF
//         {
//             free(input);
//             break;
//         }

//         if (*input)
//             add_history(input); // Adicionar entrada ao histórico

//         tokens = split_input(input); // Quebrar entrada em tokens
//         if (!tokens)
//         {
//             printf("Erro ao processar a entrada.\n");
//             free(input);
//             continue;
//         }

//         printf("\n=== Entrada Original ===\n");
//         print_tokens(tokens); // Mostrar tokens originais

//         sorted = mult_lexic_sort(tokens); // Processar e ordenar
//         printf("\n=== Tokens Ordenados ===\n");
//         print_tokens(sorted); // Mostrar tokens ordenados

//         // Liberar memória
//         free_args(tokens);
//         free_args(sorted);
//         free(input);
//     }

//     return 0;
// }


