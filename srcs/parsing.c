#include "../includes/minishell.h"

char **parse_input(char * input)
{
    char **tokens;
    int i;

    i = 0;
    tokens = malloc(sizeof(char *) * (MAX_TOKENS + 1));
    if (!tokens)
        return (NULL);
    while (*input)
    {
        while (*input == ' ')
            input++;
        if (*input =='\'')
        {
            input++;
            tokens[i++] = ft_extract_quote(&input, '\'');
        }
        else if (*input == '"')
        {
            input++;
            tokens[i++] = ft_extract_quote(&input, '"');
        }
        else
            tokens[i++] = ft_extract_word(&input);
    }
    tokens[i] = NULL;
    return(tokens);
}

char *ft_extract_quote(char **input, char quote)
{
    char *start;
    char *word;
    size_t len;

    start = *input;
    len = 0;
    while (**input && **input != quote)
    {
        (*input)++;
        len++;
    }
    word = ft_substr(start, 0, len);
    if (**input == quote)
        (*input)++;
    return (word);
}

char *ft_extract_word(char **input)
{
    char *start;
    char *word;
    size_t len;

    start = *input;
    len = 0;
    while (**input && **input != ' ' && **input != '\'' && **input != '"')
    {
        (*input)++;
        len++;
    }
    word = ft_substr(start, 0, len);
    return (word);
}


