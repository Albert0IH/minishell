/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:17:13 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/16 18:54:56 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print(char **args, int i)
{
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}

int	ft_echo(char **args)
{
	int	i;
	int	new_line;
	int	j;

	i = 1;
	new_line = 1;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 2;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j])
		{
			new_line = 1;
			break ;
		}
		new_line = 0;
		i++;
	}
	ft_print(args, i);
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
