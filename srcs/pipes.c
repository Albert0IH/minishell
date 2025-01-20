/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:10:22 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/20 17:07:40 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void split_pipes(char *input, char **commands)
{
    int i;
    char *tokens;

    t_parse states;
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


