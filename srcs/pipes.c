/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:10:22 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/06 15:42:59 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void split_pipes(char *input, char **commands)
{
    int i;
    char *tokens;

    t_tokenizer states;
    tokens = ft_strtok(input, "|", &states);
    i = 0;
    while (tokens)
    {
        commands[i] = tokens;
        tokens = ft_strtok(NULL, "|", &states);
        i++;
    }
    commands[i] = NULL;
}


