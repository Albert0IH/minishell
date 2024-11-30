/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:50:50 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/30 01:30:57 by ahamuyel         ###   ########.fr       */
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
# define MAX_INPUT_SIZE 1024
# define MAX_ARG_SIZE 100

// Parsing
char	*my_strtok(char *str, const char *delim);
void	parse_input(char *input, char **args);
void	execute_cmd(char **input);

// Execution
void	execute_cmd(char **input);

// Signals
void	handle_signal(int sig);
void	setup_signals(void);

#endif
