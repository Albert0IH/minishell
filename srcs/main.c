/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:11:09 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/25 15:19:57 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
    char *args[MAX_ARG_SIZE];
    char *rl;
	int i = 0; 
    while (1)
    {
     
        rl = readline("minishell> ");
	if (!rl)
	{
		printf("exit\n");
		break;
	}
        parse_input(rl, args);
	while (args[i] != NULL)
	{
   		printf("%s\n",args[i]);
    		i++; 
	}
	free(rl);
    }
    return 0;
}

