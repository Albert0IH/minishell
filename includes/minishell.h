/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:50:50 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/25 15:24:13 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# define BUFFER_SIZE 42

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <string.h>
#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 100

char	*my_strtok(char *str, const char *delim);
void	parse_input(char *input, char **args);

#endif
