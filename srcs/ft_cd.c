/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:18:07 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/16 16:37:28 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(char **args)
{
	if (!args[1])
		return (chdir(getenv("HOME")));
	else
	{
		if (chdir(args[1]))
			ft_putstr_fd("cd", STDERR_FILENO);
	}
	return (0);
}
