#include "../includes/minishell.h"

char **parse_input(char * args)
{
    char **tokens;
    int i;

    i = 0;
    tokens = malloc(sizeof(char *) * (MAX_ARGS + 1));
    if (!tokens)
        return (NULL);
    while (*args)
    {
        while (*args == ' ')
            args++;
        if (*args =='\'')
        {
            args++;
            tokens[i++] = extract_quote(&args, '\'');
        }
        else if (*args == '"')
        {
            args++;
            tokens[i++] = extract_quote(&args, '"');
        }
        else
            tokens[i++] = extract_word(&args);
    }
    tokens[i] = NULL;
    return(tokens);
}

char *extract_quote(char **args, char quote)
{
    char *start;
    char *word;
    size_t len;

    start = *args;
    len = 0;
    while (**args && **args != quote)
    {
        (*args)++;
        len++;
    }
    word = ft_substr(start, 0, len);
    if (**args == quote)
        (*args)++;
    return (word);
}

char *extract_word(char **args)
{
    char *start;
    char *word;
    size_t len;

    start = *args;
    len = 0;
    while (**args && **args != ' ' && **args != '\'' && **args != '"')
    {
        (*args)++;
        len++;
    }
    word = ft_substr(start, 0, len);
    return (word);
}

