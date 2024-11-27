/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:09:09 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/27 14:22:31 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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
    char *expanded_str;
    char *env_var = NULL;
    size_t len = 0;
    size_t total_len = 0;

    expanded_str = malloc(1);
    expanded_str[0] = '\0';

    while (str[len])
    {
        if (str[len] == '$')  // Encontra variáveis de ambiente
        {
            size_t start = len + 1;
            while (str[start] && (isalnum(str[start]) || str[start] == '_'))
                start++;

            env_var = get_env_var(str + len + 1); // Extrai a variável de ambiente
            if (env_var)
            {
                expanded_str = realloc(expanded_str, total_len + strlen(env_var) + 1);
                strcpy(expanded_str + total_len, env_var);
                total_len += strlen(env_var);
                len = start - 1;
            }
        }
        else
        {
            expanded_str = realloc(expanded_str, total_len + 2);
            expanded_str[total_len] = str[len];
            expanded_str[total_len + 1] = '\0';
            total_len++;
        }
        len++;
    }

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
    else if (chdir(args[1]) != 0)
    {
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

int builtin_exit(void)
{
    printf("minishell: exiting...\n");
    exit(0);
}

int builtin_env(void)
{
    extern char **environ;
    int i = 0;
    while (environ[i])
    {
        printf("%s\n", environ[i++]);
    }
    return 0;
}

int execute_external_command(char **args)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        return -1;
    } else if (pid == 0) {  // Processo filho
        if (execvp(args[0], args) == -1) {  // Executa o comando
            char *path = get_env_var("PATH");
            if (path) {
                char *cmd_path = malloc(strlen(path) + strlen(args[0]) + 2);
                if (cmd_path) {
                    char *dir = strtok(path, ":");
                    while (dir) {
                        sprintf(cmd_path, "%s/%s", dir, args[0]);
                        if (access(cmd_path, X_OK) == 0) {
                            execvp(cmd_path, args);  // Tenta executar o comando
                            break;
                        }
                        dir = strtok(NULL, ":");
                    }
                    free(cmd_path);
                }
            }
            perror("execvp failed");  // Caso não encontre o comando
            exit(1);
        }
    } else {  // Processo pai
        wait(NULL);  // Espera o filho terminar
    }
    return 0;
}


int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char **args;

    while (1)
    {
        printf("minishell> ");
        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            perror("getline");
            break;
        }

        line[nread - 1] = '\0';  // Remove a nova linha do final

        args = malloc(2 * sizeof(char *));
        args[0] = line;
        args[1] = NULL;

        if (!is_builtin(args)) {
            execute_external_command(args);  // Executa comandos externos
        }

        free(args);
    }

    free(line);
    return 0;
}
