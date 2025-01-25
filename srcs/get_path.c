/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinis <adinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:40:04 by adinis            #+#    #+#             */
/*   Updated: 2025/01/25 11:57:08 by adinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*get_command_path(char *cmd, t_path *path_info, char **environ)
{
	char	*path;
	char	*dir;
	char	*tmp;
	int		i;

	i = 0;
	path = ft_get_env("PATH", environ);
	if (!path)
		return (NULL);
	if (cmd[0] == '/')
		return (cmd);
	path_info->directories = ft_split(path, ':');
	while (path_info->directories[i])
	{
		dir = path_info->directories[i];
		tmp = ft_strjoin(dir, "/");
		path_info->full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(path_info->full_path, F_OK))
		{
			free_args(path_info->directories);
			return (path_info->full_path);
		}
		free(path_info->full_path);
		i++;
	}
	free_args(path_info->directories);
	return (NULL);
}
