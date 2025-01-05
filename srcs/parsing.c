#include "../includes/minishell.h"

char *ft_strtok(char *line, const char *delim, t_tokenizer *state)
{
    char *start;

    /*
    ------ Inicializar a estrutura que lida
    -- com o estado dos stokens, no caso
    -- de for recebido uma string como prompt
    */
    if (line)
    {
        state->current = line;
        state->in_single_quote = 0;
        state->in_double_quote = 0;
    }

    if (!state->current)
        return (NULL);
    /*
    ------ Ignorar delimitadores iniciais
    -- até encontrar uma aspa, que representa
    -- o proximo caractere util da string
    */
    while (*state->current && ft_strchr(delim, *state->current) && !state->in_double_quote && !state->in_single_quote)
        state->current++;
    if (*state->current == '\0')
        return (NULL);
    //---- Marcar o inicio do token
    start = state->current;
    /*
    ------ Avançar até encontrar um delimitador fora de aspas
    ------ Preserva os delimitadores dentro de aspas
    */
    while (*state->current)
    {
        if (*state->current == '\'' && !state->in_double_quote)
            state->in_single_quote = !state->in_single_quote;
        else if (*state->current == '"' && !state->in_single_quote)
            state->in_double_quote = !state->in_double_quote;
        else if (ft_strchr(delim, *state->current) && !state->in_single_quote && !state->in_double_quote)
            break ;
        state->current++;
    }
    /*
    ----- Verifica se as aspas foram fechadas
    */
    if (*state->current == '\0' && (state->in_single_quote || state->in_double_quote))
    {
        ft_putstr_fd("Error: Unclosed quote detected.", 2);
        //exit(EXIT_FAILURE);
        return (NULL);
    }
    /*
    ----- Finaliza o token
    */
    if (*state->current)
    {
        *state->current = '\0';
        state->current++;
    }
    /*
    ----- Retorna um ponteiro para o inicio
    -- do token que acabou de ser extraído
    -- considerndo a finalizacão a cima por '\0'
    */
    return (start);
}

char *extract_word(char *token)
{
    char *word;
    int i;
    int j;
    int in_single_quote;
    int in_double_quote;

    if (!token)
        return (NULL);
    word = malloc(ft_strlen(token) + 1);
    if (!word)
        return (NULL);
    i = 0;
    j = 0;
    in_single_quote = 0;
    in_double_quote = 0;
    while (token[i])
    {
        if (token[i] == '\'' && !in_double_quote)
            in_single_quote = !in_single_quote;
        else if (token[i] == '"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        else
            word[j++] = token[i];
        i++;
    }
    word[j] = '\0';
    return (word);
}

void tokenize_line(char *line, char **input)
{
    int i;
    char *token;
    char *word;
    t_tokenizer state;

    line[ft_strcspn(line, "\n")] = '\0';
    token = ft_strtok(line, " ", &state);
    i = 0;
    while (token)
    {
        word = extract_word(token);
        if (word)
            input[i++] = word;
        token = ft_strtok(NULL, " ", &state);
    }
    input[i] = NULL;
}

void print_tokens(char **tokens)
{
    int i;

    i = 0;
    while (tokens[i])
    {
        printf("Token %d: %s\n", i, tokens[i]);
        i++;
    }
}