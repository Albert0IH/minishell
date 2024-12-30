#include "../includes/minishell.h"
char **environ;
// Função para identificar built-ins
int is_builtin(char *cmd)
{
    if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0 ||
        ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 ||
        ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0 ||
        ft_strcmp(cmd, "exit") == 0)
        return (1);
    return (0);
}

// Função para executar as built-ins
int execute_builtin(char **args)
{
    if (ft_strcmp(args[0], "cd") == 0)
        return (builtin_cd(args));
    else if (ft_strcmp(args[0], "echo") == 0)
        return (builtin_echo(args));
    else if (ft_strcmp(args[0], "pwd") == 0)
        return (builtin_pwd());
    else if (ft_strcmp(args[0], "export") == 0)
        return (builtin_export(args));
    else if (ft_strcmp(args[0], "unset") == 0)
        return (builtin_unset(args));
    else if (ft_strcmp(args[0], "env") == 0)
        return (builtin_env());
    else if (ft_strcmp(args[0], "exit") == 0)
        return (builtin_exit(args));
    return (-1);
}

// Built-in: cd
int builtin_cd(char **args)
{
    if (!args[1])
        return (chdir(getenv("HOME")));
    if (chdir(args[1]) == -1)
    {
        perror("cd");
        return (1);
    }
    return (0);
}

// Built-in: echo
int builtin_echo(char **args)
{
    int i = 1;
    int newline = 1;

    if (args[1] && ft_strcmp(args[1], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], STDOUT_FILENO);
        if (args[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        i++;
    }
    if (newline)
        ft_putchar_fd('\n', STDOUT_FILENO);
    return (0);
}

// Built-in: pwd
int builtin_pwd(void)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)))
    {
        ft_putstr_fd(cwd, STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
        return (0);
    }
    perror("pwd");
    return (1);
}

// Built-in: export
int builtin_export(char **args)
{
    int i = 1;

    if (!args[1])
    {
        // Exibe todas as variáveis de ambiente ordenadas
        char **env = environ;
        while (*env)
        {
            ft_putstr_fd("declare -x ", STDOUT_FILENO);
            ft_putstr_fd(*env, STDOUT_FILENO);
            ft_putchar_fd('\n', STDOUT_FILENO);
            env++;
        }
        return (0);
    }
    while (args[i])
    {
        if (ft_strchr(args[i], '='))
        {
            char *key = ft_substr(args[i], 0, ft_strchr(args[i], '=') - args[i]);
            char *value = ft_strdup(ft_strchr(args[i], '=') + 1);
            setenv(key, value, 1);
            free(key);
            free(value);
        }
        else
            setenv(args[i], "", 1);
        i++;
    }
    return (0);
}

// Built-in: unset
int builtin_unset(char **args)
{
    int i = 1;

    while (args[i])
    {
        unsetenv(args[i]);
        i++;
    }
    return (0);
}

// Built-in: env
int builtin_env(void)
{
    char **env = environ;

    while (*env)
    {
        ft_putstr_fd(*env, STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
        env++;
    }
    return (0);
}

// Built-in: exit
int builtin_exit(char **args)
{
    int exit_code = 0;

    if (args[1])
        exit_code = ft_atoi(args[1]);
    exit(exit_code);
}

// Modificação na execução de comandos
// void execute_command(char *cmd)
// {
//     char *args[100];
//     char *cmd_path;

//     tokenize_inputs(cmd, args);
//     if (is_builtin(args[0]))
//     {
//         if (handle_redirections(args) < 0)
// 		    return; // Falha ao configurar redirecionamentos
//         execute_builtin(args);
//         return;
//     }
//     cmd_path = get_command_path(args[0]);
//     if (handle_redirections(args) < 0)
// 		exit(EXIT_FAILURE); // Falha ao configurar redirecionamentos
    
//     if (cmd_path == NULL)
//     {
//         ft_putstr_fd("Command not found: ", 2);
//         ft_putstr_fd(args[0], 2);
//         ft_putstr_fd("\n", 2);
//         exit(EXIT_FAILURE);
//     }
//     if (execve(cmd_path, args, environ) == -1)
//     {
//         perror("execve");
//         exit(EXIT_FAILURE);
//     }
// }


// void execute_command(char *cmd)
// {
//     char *args[100];
//     char *cmd_path;

//     tokenize_inputs(cmd, args);
//     if (is_builtin(args[0]))
//     {
//         if (handle_redirections(args) < 0)
// 		    return; // Falha ao configurar redirecionamentos
//         execute_builtin(args);
//         return;
//     }
//     cmd_path = get_command_path(args[0]);
//     if (cmd_path == NULL)
//     {
//         ft_putstr_fd("Command not found: ", 2);
//         ft_putstr_fd(args[0], 2);
//         ft_putstr_fd("\n", 2);
//         return;
//     }
//     if (handle_redirections(args) < 0)
//     {
// 		ft_putstr_fd("Redirection error\n", 2);
//         return;
//     }
//     if (execve(cmd_path, args, environ) == -1)
//     {
//         perror("execve");
//         exit(EXIT_FAILURE);
//     }
// }

void execute_command(char *cmd)
{
    char *args[100];
    char *cmd_path;
    int saved_stdout, saved_stdin;

    tokenize_inputs(cmd, args);

    if (is_builtin(args[0]))
    {
        if (handle_redirections(args, &saved_stdout, &saved_stdin) < 0)
            return; // Falha ao configurar redirecionamentos

        execute_builtin(args);

        // Restaurar os descritores originais
        dup2(saved_stdout, STDOUT_FILENO);
        dup2(saved_stdin, STDIN_FILENO);
        close(saved_stdout);
        close(saved_stdin);
        return;
    }

    cmd_path = get_command_path(args[0]);
    if (cmd_path == NULL)
    {
        ft_putstr_fd("Command not found: ", STDERR_FILENO);
        ft_putstr_fd(args[0], STDERR_FILENO);
        ft_putstr_fd("\n", STDERR_FILENO);
        return;
    }

    if (handle_redirections(args, &saved_stdout, &saved_stdin) < 0)
    {
        ft_putstr_fd("Redirection error\n", STDERR_FILENO);
        return;
    }

    if (execve(cmd_path, args, environ) == -1)
    {
        perror("execve");
        exit(EXIT_FAILURE);
    }

    // Restaurar os descritores originais
    dup2(saved_stdout, STDOUT_FILENO);
    dup2(saved_stdin, STDIN_FILENO);
    close(saved_stdout);
    close(saved_stdin);
}

