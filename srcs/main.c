/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:11:09 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/26 17:38:19 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char *input;
	char **tokens;
	//int i;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		tokens = tokenize(input);
		if (tokens)
		{
			if (tokens[0])
				exec_comand(tokens);
			free_tokens(tokens);
		}
		// if (tokens)
		// {
		// 	i = 0;
		// 	while (tokens[i])
		// 	{
		// 		printf("%s\n", tokens[i]);
        //         i++;
		// 	}
		// free_tokens(tokens);
		// }
		free(input);
	}
	return (0);
}


// int main(void) {
//     char *input;
//     char **tokens;

//     while (1) {
//         // Lê a linha de comando com readline
//         input = readline("minishell> ");
//         if (!input) {
//             printf("exit\n");
//             break;
//         }

//         // Adiciona o comando ao histórico
//         if (*input)
//             add_history(input);

//         // Tokeniza a linha de comando
//         tokens = tokenize(input);
//         if (tokens) {
//             int i = 0;
//             while (tokens[i]) {
//                 printf("Token %d: %s\n", i, tokens[i]);
//                 i++;
//             }
//             // Libera a memória dos tokens após o uso
//             free_tokens(tokens);
//         }

//         // Libera a memória do input
//         free(input);
//     }
//     return 0;
// }