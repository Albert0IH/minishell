/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:39:59 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/07 09:41:57 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

extern char **environ;

typedef struct s_tokenizer
{
	char	*current;
	int		in_single_quote;
	int		in_double_quote;
}			t_tokenizer;

typedef struct s_path
{
	char	**environ;
	char	*full_path;
	char	**directories;
	char	*path;
}			t_path;

typedef struct t_env_var{
    char *name;
    char *value;
} s_env_var;


// Signals
void		handle_signal(int sig);
void		setup_signals(void);
// Parsing
char		*ft_strtok(char *line, const char *delim, t_tokenizer *state);
char		*extract_word(char *token);
void		tokenize_line(char *line, char **input);
void		print_tokens(char **tokens);
// Execute
void		exec_command(char *cmd);
void		execute(char **commands);
void	init_path(t_path *path_info);
// Builtins
int			is_builtin(char *cmd);
int			exec_builtin(char **args);
int			ft_echo(char **args);
int			ft_cd(char **args);
int			ft_pwd(void);
int ft_export(char **args);
int ft_unset(char **args);
int ft_env(void);
int			ft_exit(char **args);
// Redir
int			handle_redir(char **args, int *saved_stdout, int *saved_stdin);
// Pipes
void		split_pipes(char *input, char **cmd);
#endif