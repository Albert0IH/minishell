/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:20:49 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/02/04 10:29:21 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_env_var(char *var_name, char ***environ)
{
	int		i;
	char	**new_environ;
	int		len;
	int		size;
	int		j;

	len = strlen(var_name);
	size = count_lines(*environ);
	new_environ = malloc(sizeof(char *) * (size));
	i = 0;
	j = 0;
	while (i < size)
	{
		if (!ft_strncmp((*environ)[i], var_name, len)
			&& ((*environ)[i][len] == '=' || (*environ)[i][len] == '\0'))
		{
			i++;
			continue ;
		}
		new_environ[j++] = ft_strdup((*environ)[i++]);
	}
	//new_environ[j] = NULL;
	free_args(*environ);
	*environ = new_environ;
}

int	ft_unset(char **args, char ***environ)
{
	char	*var_to_unset;
	int		i;

	if (args[1] == NULL)
		return (0);
	i = 1;
	while (args[i])
	{
		var_to_unset = args[i];
		remove_env_var(var_to_unset, environ);
		i++;
	}
	return (1);
}
