/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:56:44 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/24 16:15:24 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_operator(char *s)
{
	if (!ft_strcmp(s, ">") || !ft_strcmp(s, ">>") || !ft_strcmp(s, "<")
		|| !ft_strcmp(s, "<<"))
		return (1);
	return (0);
}

typedef struct s_lexic
{
    char *cmd;
    char *operador;
    char *file;
}		t_lexic;

void	sort_lexic(char **av)
{
	char	*cmd;
	char	*oprd;
	char	*file;
    int i;
	cmd = av[2];
	oprd = av[0];
	file = av[1];
	av[0] = cmd;
	av[1] = oprd;
    av[2] = file;

    i = 2;
    while (av[i])
    {
        file = ft_strjoin(file, av[i + 1]);
        i++;
    }
}
