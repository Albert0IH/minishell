/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:39:59 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/27 19:41:20 by ahamuyel         ###   ########.fr       */
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
void		init_path(t_path *path_info);
// Environ
char		**ft_environ(char **environ);
char		*ft_get_env(char *var, char **environ);
char		*get_command_path(char *cmd, t_path *path_info, char **environ);
// Parsing
char		*ft_strtok(char *line, const char *delim, t_parse *state);
char		**tokenize_line(char *line, char **environ);
char		*expand_env_vars(const char *s, char **environ);
// Lexic
char		**mult_lexic_sort(char **input);
// Execute
void		execute_from_path(char **commands, char **environ);
void		execute_command(char *line, char **environ);
// Clean
void		free_args(char **args);
void		free_tokens(char **tokens);

#endif
