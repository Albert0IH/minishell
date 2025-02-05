/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:20:49 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/16 16:37:57 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_unset(char **args, char **environ)
{
	char	*var_to_unset;
	int		i;
	int		len;

	if (args[1] == NULL)
		return (0);
	i = 0;
	var_to_unset = args[1];
	len = strlen(var_to_unset);
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], var_to_unset, len) == 0
			&& environ[i][len] == '=')
		{
			while (environ[i] != NULL)
			{
				environ[i] = environ[i + 1];
				i++;
			}
			return (0);
		}
		i++;
	}
	return (1);
}
