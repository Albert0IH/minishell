/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:19:05 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/02/04 15:46:45 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_search_on_env(char **array, char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[len] && s[len] != '=')
		len++;
	while (array[i])
	{
		if (!ft_strncmp(array[i], s, len))
			return (1);
		i++;
	}
	return (0);
}

int	ft_env(char **environ, char **av, t_path *path)
{
	int	i;

	if (av[1])
	{
		printf("env: %s: No such file or directory\n", av[1]);
		path->status = 127;
		return (127);
	}
	i = 0;
	while (environ[i])
	{
		if (!ft_searc_char(environ[i], '?') && ft_searc_char(environ[i], '='))
			printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}
