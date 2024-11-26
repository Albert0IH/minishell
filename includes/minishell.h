/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:50:50 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/26 17:44:45 by ahamuyel         ###   ########.fr       */
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
# include <sys/wait.h>
# include <string.h>
# include <unistd.h>

// parse input
char	*ft_strtok(char *str, const char *delim);
int		count_tokens(char *line);
char	**tokenize(char *input);
void	free_tokens(char **tokens);

// execute comand
void	exec_comand(char **args);
#endif