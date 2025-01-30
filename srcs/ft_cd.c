/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:18:07 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/30 18:00:11 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(char **args, t_path *path)
{
	if (!args[1])
		return (chdir(getenv("HOME")));
	else
	{
		if (chdir(args[1]))
		{
			path->status = 1;
			return(ft_putstr_fd("cd: d: No such file or directory\n", STDERR_FILENO), 1);
		}
	}
	return (0);
}
