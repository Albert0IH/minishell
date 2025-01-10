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
	return (0);
}

int	exec_builtin(char **args)
{
	if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(args));
	if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args));
	if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(args[0], "export"))
		return (ft_export(args));
	if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(args));
	if (!ft_strcmp(args[0], "env"))
		return (ft_env());
    // if (!ft_strcmp(args[0], "exit"))
	// 	return (ft_exit(args));
	return (-1);
}

char *ft_strcat(char *dest, const char *src) {
    char *ptr = dest;
    while (*ptr != '\0') ptr++;
    while (*src != '\0') *ptr++ = *src++;
    *ptr = '\0';
    return dest;
}
char *ft_strcpy(char *dest, const char *src) {
    char *ptr = dest;
    while ((*ptr++ = *src++));
    return dest;
}
int	ft_echo(char **args)
{
	int	i;
	int	new_line;

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

int	ft_cd(char **args)
{
	if (!args[1])
		return (chdir(getenv("HOME")));
	else
	{
		if (chdir(args[1]))
			ft_putstr_fd("cd", STDERR_FILENO);
	}
	return (0);
}

int	ft_pwd(void)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)))
	{
		ft_putstr_fd(pwd, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else
		ft_putstr_fd("pwd\n", STDOUT_FILENO);
	return (0);
}

char *create_env_var(char *name, char *value)
{
    int var_len;
    int value_len;
    char *new_env_var;

    var_len = ft_strlen(name);
    value_len = ft_strlen(value);
    new_env_var = malloc(var_len + value_len + 2);
    if (!new_env_var)
    {
        perror("malloc");
        return NULL;
    }
    ft_strcpy(new_env_var, name);
    ft_strcat(new_env_var, "=");
    ft_strcat(new_env_var, value);

    return new_env_var;
}

void add_or_update_env_var(char *var_name, char *var_value)
{
    int i;
    int var_len;
    char *new_env_var;

    i = 0;
    var_len = ft_strlen(var_name);
    while (!environ[i])
    {
        if (!ft_strncmp(environ[i], var_name, var_len) && environ[i][var_len] == '=')
        {
            new_env_var = create_env_var(var_name, var_value);
            if (!new_env_var)
                return;
            environ[i] = new_env_var;
            return;
        }
        i++;
    }
    new_env_var = create_env_var(var_name, var_value);
    if (!new_env_var)
        return ;
    environ[i] = new_env_var;
    environ[i + 1] = NULL;
}

void show_env()
{
	int i;

	i = 0;
	while (!environ[i])
		printf("declare - x %s\n", environ[i++]);
}
int ft_export(char **args)
{
	char *equals_sign;
	if (!args[1])
		return (show_env(), 0);
	equals_sign = ft_strchr(args[1], '=');
	if (!equals_sign)
		return (fprintf(stderr, "export: `%s': not a valid identifier\n", args[1]), 1);
	*equals_sign = '\0'; // Temporariamente substitui '=' por '\0' para isolar o nome
	add_or_update_env_var(args[1], equals_sign + 1);
	*equals_sign = '='; // Restaura o sinal de igualdade
	return (0);
}

int ft_unset(char **args)
{
    char *var_to_unset;
    int i;
    int len;

    if (args[1] == NULL)
        return (0);
    i = 0;
    var_to_unset = args[1];
    len = strlen(var_to_unset);
    while (environ[i] != NULL)
    {
        if (strncmp(environ[i], var_to_unset, len) == 0 && environ[i][len] == '=')
        {
            while (environ[i] != NULL)
            {
                environ[i] = environ[i + 1];
                i++;
            }
            return (0);
        }
        i++;
    }
	return (1);
}

int ft_env(void)
{
    int i;

    i = 0;
    while (environ[i] != NULL)
    {
        printf("%s\n", environ[i]);
        i++;
    }
	return (0);
}
