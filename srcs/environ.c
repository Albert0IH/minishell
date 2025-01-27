/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:15:11 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/27 14:35:59 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_environ(char **environ)
{
	char	**env;
	int		i;
	int		len;

	env = malloc(sizeof(char *) * (count_lines(environ) + 1));
	i = 0;
	while (environ[i])
	{
		len = strlen(environ[i]);
		env[i] = malloc(sizeof(char) * (len + 1));
		strcpy(env[i], environ[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

char	*ft_get_env(char *var, char **environ)
{
	int		i;
	size_t	var_len;

	if (!var || !environ)
		return (NULL);
	var_len = ft_strlen(var);
	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], var, var_len) && environ[i][var_len] == '=')
			return (environ[i] + var_len + 1);
		i++;
	}
	return (NULL);
}
