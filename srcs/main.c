#include "../includes/minishell.h"

int main ()
{
    char *input;

    while (1)
    {
        input = readline("minishell> ");
        if(!input || !ft_strcmp(input, "exit"))
        {
            free(input);
            return (0);
        }
    }
    free(input);
    return (0);
}