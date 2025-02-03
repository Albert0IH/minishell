/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:20:49 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/02/03 18:38:02 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_unset(char **args, char ***environ)
{
	char	*var_to_unset;
	int		i;
	int		len;
	int		j;

	if (args[1] == NULL)
		return (0);
	i = 1;
	while (args[i])
	{
		var_to_unset = args[i];
		len = strlen(var_to_unset);
		j = 0;
		while (*environ[j])
		{
			if (ft_strncmp(*environ[j], var_to_unset, len) == 0
				&& ((*environ)[j][len] == '=' || (*environ)[j][len] == '\0'))
			{
				while (*environ[j])
				{
					*environ[j] = *environ[j + 1];
					j++;
				}
				continue ;
			}
			j++;
		}
		i++;
	}
	return (1);
}
