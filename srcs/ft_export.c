/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:16:09 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/02/03 18:59:52 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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


void	add_or_update_env_var(char *line, char *var_name, char *var_value,
		char ***environ)
{
	int		i;
	char	*new_var;
	int		len;
	int		size;
	char	**new_environ;

	len = strlen(var_name);
	i = 0;
	while ((*environ)[i])
	{
		if (!strncmp((*environ)[i], var_name, len) && ((*environ)[i][len] == '='
				|| (*environ)[i][len] == '\0'))
		{
			new_var = create_env_var(line, var_name, var_value);
			if (!new_var)
				return ;
			free((*environ)[i]);
			(*environ)[i] = new_var;
			return ;
		}
		i++;
	}
	new_var = create_env_var(line, var_name, var_value);
	if (!new_var)
		return ;
    size = count_lines(*environ);
    new_environ = malloc(sizeof(char *) * (size + 2));
    i = 0;
    while (i < (size))
    {
        new_environ[i] = ft_strdup((*environ)[i]);
        i++;
    }
    new_environ[i] = new_var;
    new_environ[i + 1] = NULL;
    free_args(*environ);
    *environ = new_environ;
}



void	show_env(char **environ)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (environ[i])
	{
		if (ft_searc_char(environ[i], '?'))
			i++;
		else
		{
			name = ft_extract_name(environ[i]);
			value = ft_extract_value(environ[i]);
			if (!ft_searc_char(environ[i], '='))
				printf("declare -x %s\n", name);
			else
				printf("declare -x %s=\"%s\"\n", name, value);
			i++;
			free(value);
			free(name);
		}
	}
}

int	ft_export(char **args, char ***environ)
{
	char	*equals_sign;
	char	*line;
	int		i;

	i = 1;
	if (!args[1])
		return (show_env(*environ), 0);
	while (args[i])
	{
		if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
			return (ft_putstr_fd("export: not a valid identifier\n",
					STDERR_FILENO), 1);
		line = ft_strdup(args[i]);
		equals_sign = ft_strchr(line, '=');
		if (!equals_sign)
		{
			add_or_update_env_var(args[i], line, "", environ);
			i++;
			continue ;
		}
		*equals_sign = '\0';
		add_or_update_env_var(args[i], line, equals_sign + 1, environ);
		i++;
	}
	free(line);
	return (0);
}
