/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:16:09 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/18 07:25:30 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	name = malloc(i + 1);
	if (!name)
		return (NULL);
	ft_strncpy(name, s, i);
	name[i] = '\0';
	return (name);
}

char	*ft_extract_value(char *s)
{
	char	*value;
	char	*start;

	start = ft_strchr(s, '=');
	if (!start)
		return (NULL);
	start++;
	value = ft_strdup(start);
	return (value);
}

char	*create_env_var(char *line, char *name, char *value)
{
	int		var_len;
	int		value_len;
	char	*new_env_var;

	var_len = ft_strlen(name);
	value_len = ft_strlen(value);
	new_env_var = malloc(var_len + value_len + 2);
	if (!new_env_var)
	{
		perror("malloc");
		return (NULL);
	}
	new_env_var = ft_strdup(name);
	if (ft_searc_char(line, '='))
		ft_strcat(new_env_var, "=");
	ft_strcat(new_env_var, value);
	return (new_env_var);
}

void	add_or_update_env_var(char *line, char *var_name, char *var_value,
		char **environ)
{
	int		i;
	int		var_len;
	char	*new_env_var;

	i = 0;
	var_len = ft_strlen(var_name);
	while (environ[i])
	{
		if (ft_strncmp(environ[i], var_name, var_len) == 0)
		{
			new_env_var = create_env_var(line, var_name, var_value);
			if (!new_env_var)
				return ;
			environ[i] = new_env_var;
			return ;
		}
		i++;
	}
	new_env_var = create_env_var(line, var_name, var_value);
	if (!new_env_var)
		return ;
	environ[i] = new_env_var;
	environ[i + 1] = NULL;
}

void	show_env(char **environ)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (environ[i])
	{
		name = ft_extract_name(environ[i]);
		value = ft_extract_value(environ[i]);
		if (!ft_searc_char(environ[i], '='))
			printf("declare - x %s\n", name);
		else
			printf("declare - x %s=\"%s\"\n", name, value);
		i++;
		free(value);
		free(name);
	}
}

int	ft_export(char **args, char **environ)
{
	char	*equals_sign;
	char	*line;
	int		i;

	if (!args[1])
		return (show_env(environ), 0);
	i = 1;
	while (args[i])
	{
		line = ft_strdup(args[i]);
		equals_sign = ft_strchr(line, '=');
		if (!equals_sign)
			add_or_update_env_var(args[i], line, "", environ);
		*equals_sign = '\0';
		if (equals_sign)
			add_or_update_env_var(args[i], line, equals_sign + 1, environ);
		i++;
	}
	return (0);
}