/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:39:59 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/24 15:00:56 by ahamuyel         ###   ########.fr       */
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

typedef struct s_env_var
{
	char	*name;
	char	*value;
}			t_env_var;

// Signals
void		handle_signal(int sig);
void		setup_signals(void);
// Parsing
void		init_state(t_parse *state);
char		*ft_strtok(char *line, const char *delim, t_parse *state);
char		*extract_word(t_parse *state, char *token, char **environ);
void		tokenize_line(char *line, char **input, char **environ);
void		print_tokens(char **tokens);
// Lexic
int			is_operator(char *s);
void		sort_lexic(char **av);
// Expand
char		*get_env_value(char *var, char **environ);
char		*expand_env_vars(const char *s, char **environ);
// Execute
char		*ft_get_env(char *var, char **environ);
char		*get_command_path(char *cmd, t_path *path_info, char **environ);
void		execute_command(char *line, char **environ);
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
// Clean
void		free_args(char **args);
void		free_tokens(char **tokens);
char		*ft_strncpy(char *dest, const char *src, size_t n);

#endif
