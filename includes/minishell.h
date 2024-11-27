/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:50:50 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/27 11:45:00 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE 42

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// Parsing
char	*ft_strtok(char *str, const char *delim);
char	**tokenize(char *input);
void	free_tokens(char **tokens);

// Execution
void	exec_command(char **args);
char	*find_exec(char *command);

// Builtins
int		is_builtin(char **args);
int		builtin_cd(char **args);
int		builtin_echo(char **args);
int		builtin_exit(void);
int		builtin_env(void);

// Utilities
char	*remove_quotes(const char *arg);
char	*expand_env_vars(char *arg);

#endif
