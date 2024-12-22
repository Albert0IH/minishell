#include "../includes/minishell.h"

char *extract_quote(char **input, char quote)
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

char *extract_word(char **input)
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

void extracting(char **input, char **tokens, int *i)
{
    while (**input == ' ')
        (*input)++;
    if (**input == '\'')
    {
        (*input)++;
        tokens[(*i)++] = extract_quote(input, '\'');
    }
    else if (**input == '"')
    {
        (*input)++;
        tokens[(*i)++] = extract_quote(input, '"');
    }
    else
        tokens[(*i)++] = extract_word(input);
}   

char **parse_input(char *input)
{
    char **tokens;
    int i;

    i = 0;
    tokens = malloc(sizeof(char *) * (MAX_ARGS + 1));
    if (!tokens)
        return (NULL);
    while (*input)
        extracting(&input, tokens, &i);
    tokens[i] = NULL;
    return(tokens);
}
