/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:15:09 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/02/04 08:55:07 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	execute_builtin(char **commands, char ***environ, t_path *path)
{
	if (!ft_strcmp(commands[0], "echo"))
		return (ft_echo(commands));
	if (!ft_strcmp(commands[0], "cd"))
		return (ft_cd(commands, path));
	if (!ft_strcmp(commands[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(commands[0], "export"))
		return (ft_export(commands, environ));
	if (!ft_strcmp(commands[0], "unset"))
		return (ft_unset(commands, environ));
	if (!ft_strcmp(commands[0], "env"))
		return (ft_env(*environ, commands, path));
	if (!ft_strcmp(commands[0], "exit"))
		return (ft_exit(commands));
	path->status = 127;
	return (-1);
}
