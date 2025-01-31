/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:16:09 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/31 16:38:28 by ahamuyel         ###   ########.fr       */
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
void add_or_update_env_var(char *line, char *var_name, char *var_value, char ***environ)
{
    int     i;
    char    *new_env_var;
    int     len;
    char    **new_environ;

    len = ft_strlen(var_name);
    i = 0;

    while ((*environ)[i])
    {
        if (!ft_strncmp((*environ)[i], var_name, len) &&
            ((*environ)[i][ft_strlen(var_name)] == '=' || (*environ)[i][ft_strlen(var_name)] == '\0'))
        {
            new_env_var = create_env_var(line, var_name, var_value);
            if (!new_env_var)
                return ;
            free((*environ)[i]);
            (*environ)[i] = new_env_var;
            return ;
        }
        i++;
    }

    // Se não encontrar, adiciona uma nova variável
    new_env_var = create_env_var(line, var_name, var_value);
    if (!new_env_var)
        return ;

    // Realoca o espaço para incluir o novo elemento
    new_environ = realloc(*environ, sizeof(char *) * (i + 2)); // +1 para o novo ambiente, +1 para o NULL
    if (!new_environ)
    {
        free(new_env_var); // Se falhar na realocação, libere a memória alocada
        return;
    }

    new_environ[i] = new_env_var;
    new_environ[i + 1] = NULL;  // Certifique-se de que o último valor é NULL

    *environ = new_environ;  // Atualize o ponteiro para apontar para o novo array
}

void show_env(char **environ)
{
    int     i;
    char    *name;
    char    *value;

    i = 0;
    while (environ[i])
    {
        if (ft_searc_char(environ[i], '?'))  // Correção de digitação aqui
            i++;
        else
        {
            name = ft_extract_name(environ[i]);
            value = ft_extract_value(environ[i]);
            if (!ft_searc_char(environ[i], '='))
                printf("declare -x %s\n", name);  // Ajuste do formato "declare - x"
            else
                printf("declare -x %s=\"%s\"\n", name, value);
            i++;
            free(value);
            free(name);
        }
    }
}

int ft_export(char **args, char **environ)
{
    char    *equals_sign;
    char    *line;
    int     i;

    i = 1;
    if (!args[1])
        return (show_env(environ), 0);
    while (args[i])
    {
        if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
            return (ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO), 1);
        line = ft_strdup(args[i]);
        equals_sign = ft_strchr(line, '=');
        if (!equals_sign)
        {
            add_or_update_env_var(args[i], line, "", &environ);  // Corrigido para passar como ponteiro de ponteiro
            i++;
            continue ;
        }
        *equals_sign = '\0';
        add_or_update_env_var(args[i], line, equals_sign + 1, &environ);  // Corrigido para passar como ponteiro de ponteiro
        i++;
    }
    return (0);
}
