/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:09:09 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/27 14:29:48 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char **environ;

char *get_env_var(const char *name)
{
    int i = 0;
    size_t len = strlen(name);

    while (environ[i])
    {
        if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
            return (environ[i] + len + 1); // Retorna o valor da variável de ambiente
        i++;
    }
    return NULL; // Caso não encontre a variável
}

char *expand_string(const char *str)
{
    char *expanded_str = malloc(strlen(str) + 1);  // Aloca a string final
    if (!expanded_str)
    {
        perror("malloc failed");
        exit(1);
    }

    size_t len = 0;
    while (str[len])
    {
        if (str[len] == '$')  // Encontra variáveis de ambiente
        {
            char *env_var = get_env_var(str + len + 1); // Obtém a variável de ambiente
            if (env_var)
            {
                size_t new_len = strlen(env_var);
                expanded_str = realloc(expanded_str, len + new_len + 1);  // Realoca
                if (!expanded_str)
                {
                    perror("realloc failed");
                    exit(1);
                }
                strncpy(expanded_str + len, env_var, new_len); // Adiciona a variável de ambiente
                len += new_len;
            }
            else
            {
                expanded_str[len] = '$'; // Caso a variável não seja encontrada, apenas copia o $
                len++;
            }
        }
        else
        {
            expanded_str[len] = str[len];  // Copia o caractere
            len++;
        }
    }
    expanded_str[len] = '\0';  // Finaliza a string
    return expanded_str;
}

int is_builtin(char **args)
{
    if (strcmp(args[0], "cd") == 0)
    {
        builtin_cd(args);
        return 1;
    }
    if (strcmp(args[0], "echo") == 0)
    {
        builtin_echo(args);
        return 1;
    }
    if (strcmp(args[0], "exit") == 0)
    {
        builtin_exit();
        return 1;
    }
    if (strcmp(args[0], "env") == 0)
    {
        builtin_env();
        return 1;
    }
    return 0;
}


int builtin_cd(char **args)
{
    if (!args[1])
    {
        fprintf(stderr, "minishell: cd: expected argument\n");
    }
    else
    {
        char *path = args[1];

        // Remove aspas ao redor do caminho
        if ((path[0] == '"' || path[0] == '\'') && path[strlen(path) - 1] == path[0])
        {
            path[strlen(path) - 1] = '\0'; // Remove a última aspa
            path++; // Remove a primeira aspa
        }

        if (chdir(path) != 0)
            perror("minishell");
    }
    return 0;
}





int builtin_echo(char **args)
{
    int i = 1;
    int new_line = 1;

    if (args[i] && strcmp(args[i], "-n") == 0)
    {
        new_line = 0; // Trata a opção -n
        i++;
    }

    while (args[i])
    {
        if (args[i][0] == '"' || args[i][0] == '\'')  // Verifica se a string está entre aspas
        {
            char *start = args[i] + 1;
            int len = strlen(start);
            char *str = strndup(start, len - 1);  // Remove as aspas

            // Expande variáveis de ambiente e interpreta `\n`, `\t`, etc.
            printf("%s", expand_string(str));
            free(str);
        }
        else
        {
            printf("%s", args[i]);
        }

        if (args[i + 1])
            printf(" ");
        i++;
    }

    if (new_line)
        printf("\n");

    return 0;
}



int	builtin_exit(void)
{
	printf("minishell: exiting...\n");
	exit(0);
}

int	builtin_env(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
		printf("%s\n", environ[i++]);
	return (0);
}
