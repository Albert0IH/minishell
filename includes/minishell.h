/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:39:59 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/27 17:52:22 by ahamuyel         ###   ########.fr       */
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

# define SIZE_EXPANDED 2048

typedef struct s_parse
{
	char	*current;
	int		in_single_quote;
	int		in_double_quote;
	int		i;
	int		j;
}			t_parse;

typedef struct s_path
{
	char	**environ;
	char	*full_path;
	char	**directories;
	char	*path;
}			t_path;

typedef struct s_token
{
	char	*expanded;
	char	*word;
	char	**tokens;
}			t_token;

// Suport
int			check_readline(char *line);
void		print_tokens(char **tokens);
int			count_lines(char **s);
// Signals
void		handle_signal(int sig);
void		setup_signals(void);
// Setup structs
void		init_state(t_parse *state);
void		init_token(t_token *token);
// Suport
int			ft_searc_char(char *s, char c);
int			ft_search_str(char **array, char *s);
// Environ
char		**ft_environ(char **environ);
char		*ft_get_env(char *var, char **environ);

// Parsing
char		*ft_strtok(char *line, const char *delim, t_parse *state);
char		**tokenize_line(char *line, char **environ);
char		*expand_env_vars(const char *s, char **environ);
// Lexic
char		**mult_lexic_sort(char **input);
// Execute
char		*ft_get_env(char *var, char **environ);
char		*get_command_path(char *cmd, t_path *path_info, char **environ);
void		execute_command(char *line, char **commands, char **environ);
int			execute_builtin(char **commands, char **environ);
void		execute_from_path(char **commands, char **environ);
void		execute(char **commands, char **environ);
void		init_path(t_path *path_info);
// Builtins
int			is_builtin(char *cmd);
int			ft_echo(char **args);
int			ft_cd(char **args);
int			ft_pwd(void);
int			ft_export(char **args, char **environ);
int			ft_unset(char **args, char **environ);
int			ft_env(char **environ);
int			ft_exit(char **args);
// Redir
int			handle_redir(char **args, int *saved_stdout, int *saved_stdin);
// Pipes
void		split_pipes(char *input, char **cmd);
char		**split_commands(char *input);
int			count_commands(char *input);
// Clean
void		free_args(char **args);
void		free_tokens(char **tokens);

#endif
