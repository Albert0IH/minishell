/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:38:05 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/29 17:05:08 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_cmd(char **input)
{
    pid_t pid;
    int status;

    if (!input[0])
        return ;
    pid = fork();
    if (pid == 0)
    {
        if (execve(input[0], input, NULL) == -1)
        {
            perror("minishell");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
        perror("minishell");
    else
        waitpid(pid, &status, 0);
}