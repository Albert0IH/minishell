#include "../includes/minishell.h"

int main()
{
    char *input;
    char **args;
    int i;

    while (1)
    {
        input = readline("minishell> ");
        if (!input)
        {
            printf("exit\n");
            free(input);
            break ;
        }
        if (*input)
            add_history(input);
        args = parse_input(input);
        i = 0;
        while(args[i])
        {
            printf("%s\n", args[i]);
            free(args[i++]);
        }
        free(args);
        free(input);
    }
    return (0);
}