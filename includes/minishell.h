#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_tokenizer{
    char *current;
    int in_single_quote;
    int in_double_quote;
} t_tokenizer;

typedef struct s_path{
    char **environ;
    char *full_path;
    char **directories;
    char *path;
} t_path;

//Signals
void handle_signal(int sig);
void setup_signals(void);
//Parsing
char *ft_strtok(char *line, const char *delim, t_tokenizer *state);
char *extract_word(char *token);
void tokenize_line(char *line, char **input);
void print_tokens(char **tokens);
//Execute
void exec_command(char *cmd);
//Builtins
int is_builtin(char *cmd);
int exec_builtin(char **args);
int ft_echo(char **args);
int ft_cd(char **args);
int ft_pwd(void);
//Redir
//int handle_redir(char **args);
int handle_redir(char **args, int *saved_stdout, int *saved_stdin);
#endif