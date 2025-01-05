#include "../includes/minishell.h"

int main()
{
    char *line;
    while (1)
    {
        line = readline("minishell> ");
        if (!line)
        {
            printf("exit\n");
            break ;
        }
        if (*line)
            add_history(line);
        exec_command(line);
        free(line);
    }
    return (0);
}