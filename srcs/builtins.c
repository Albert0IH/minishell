/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinis <adinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:38:05 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/12/21 15:40:48 by adinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/minishell.h"

int is_builtin(char *cmd)
{
    if (!ft_strcmp(cmd, "echo"))
        return (1);
    if (!ft_strcmp(cmd, "cd"))
        return (1);
    if (!ft_strcmp(cmd, "pwd"))
        return (1);
    return (0);
}

int exec_builtin(char **args)
{
    if (!ft_strcmp(args[0], "echo"))
        return (ft_echo(args));
    if (!ft_strcmp(args[0], "cd"))
        return (ft_cd(args));
    if (!ft_strcmp(args[0], "pwd"))
        return (ft_pwd());
    return (-1);
}

int ft_echo(char **args)
{
    int i;
    int new_line;

    i = 1;
    new_line = 1;
    if (args[1] && ft_strcmp(args[1], "-n") == 0)
    {
        new_line = 0;
        i++;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], STDOUT_FILENO);
        if (args[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        i++;
    }
    if (new_line)
        ft_putchar_fd('\n', STDOUT_FILENO);
    return (0);
}

int ft_cd(char **args)
{
    if (!args[1])
        return(chdir(getenv("HOME")));
    else
    {
        if (chdir(args[1]))
            ft_putstr_fd("cd", STDERR_FILENO);
    }
    return (0);
}

int ft_pwd(void)
{
    char pwd[1024];

    if (getcwd(pwd, sizeof(pwd)))
    {
        ft_putstr_fd(pwd, STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
    }
    else
        ft_putstr_fd("pwd\n", STDOUT_FILENO);
    return (0);
}
