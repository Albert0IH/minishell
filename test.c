/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:32:05 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/18 00:28:51 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	ft_searc_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_extract_name(char *s)
{
	char	*name;
	int		i;

	while (s[i] && s[i] != '=')
		i++;
	name = malloc(i + 1);
	if (!name)
		return (NULL);
	strncpy(name, s, i);
	name[i] = '\0';
	return (name);
}

char	*ft_extract_value(char *s)
{
	char	*value;
	char	*start;

	start = strchr(s, '=');
	if (!start)
		return ("\0");
	start++;
	value = strdup(start);
	return (value);
}

int	count_lines(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	**ft_environ(char **environ)
{
	char	**env;
	int		i;
	int		j;
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

void	ft_print_env(char **environ)
{
	int	i;

	i = 0;
	while (environ[i])
		printf("%s\n", environ[i++]);
}

void	ft_show_env(char **environ)
{
	char	*name;
	char	*value;
	char	**env;
	int		i;

	i = 0;
	while (environ[i])
	{
		name = ft_extract_name(env[i]);
		value = ft_extract_value(env[i]);
		printf("%s=\"%s\"\n", name, value);
		free(name);
		free(value);
		i++;
	}
}

int	main(int ac, char *av, char **environ)
{
	char	**env;
	char	*name;
	char	*value;
	int		i;

	(void)ac;
	(void)av;
	// env = ft_environ(environ);
	// name = ft_extract_name(env[1]);
	// value = ft_extract_value(env[1]);
	// printf("%s=\"%s\"\n", name, value);
	env = ft_environ(environ);
	ft_show_env(env);
	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
	return (0);
}
