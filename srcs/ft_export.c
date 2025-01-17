/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:16:09 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/17 11:40:17 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*create_env_var(char *name, char *value)
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
	ft_strcat(new_env_var, "=");
	ft_strcat(new_env_var, value);
	return (new_env_var);
}

void	add_or_update_env_var(char *var_name, char *var_value, char **environ)
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
			new_env_var = create_env_var(var_name, var_value);
			if (!new_env_var)
				return ;
			environ[i] = new_env_var;
			return ;
		}
		i++;
	}
	new_env_var = create_env_var(var_name, var_value);
	if (!new_env_var)
		return ;
	environ[i] = new_env_var;
	environ[i + 1] = NULL;
}

void	show_env(char **environ)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		printf("declare - x \"%s\"\n", environ[i]);
		i++;
	}
}

int	ft_export(char **args, char **environ)
{
	char	*equals_sign;

	if (!args[1])
		return (show_env(environ), 0);
	equals_sign = ft_strchr(args[1], '=');
	if (!equals_sign)
		return (fprintf(stderr, "export: `%s': not a valid identifier\n",
				args[1]), 1);
	*equals_sign = '\0';
	add_or_update_env_var(args[1], equals_sign + 1, environ);
	*equals_sign = '=';
	return (0);
}
