/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albert01h <albert01h@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:52:12 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/23 00:08:24 by albert01h        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_state(t_parse *state)
{
	state->current = NULL;
	state->in_single_quote = 0;
	state->in_double_quote = 0;
	state->i = 0;
	state->j = 0;
}

char	*ft_strtok(char *line, const char *delim, t_parse *state)
{
	char	*start;

	init_state(state);
	if (line)
		state->current = line;
	if (state->current == NULL)
		return (NULL);
	while (*state->current && ft_strchr(delim, *state->current))
		state->current++;
	if (*state->current == '\0')
		return (NULL);
	start = state->current;

	while (*state->current)
	{
		if (*state->current == '\'' && !state->in_double_quote)
			state->in_single_quote = !state->in_single_quote; // Alternar estado de aspas simples
		else if (*state->current == '"' && !state->in_single_quote)
			state->in_double_quote = !state->in_double_quote; // Alternar estado de aspas duplas
		else if (ft_strchr(delim, *state->current) && !state->in_single_quote && !state->in_double_quote)
			break;
		state->current++;
	}
	if (*state->current)
	{
		*state->current = '\0';
		state->current++;
	}
	//printf("Aqui!\n");
	return (start);
}


// #include "../includes/minishell.h"

// static void	skip_delim(t_parse *state, const char *delim)
// {
// 	while (*state->current && ft_strchr(delim, *state->current)
// 		&& !state->in_double_quote && !state->in_single_quote)
// 		state->current++;
// }

// static void	handle_quotes(t_parse *state)
// {
// 	if (*state->current == '\'' && !state->in_double_quote)
// 		state->in_single_quote = !state->in_single_quote;
// 	else if (*state->current == '"' && !state->in_single_quote)
// 		state->in_double_quote = !state->in_double_quote;
// }

// static char	*process_token(t_parse *state, const char *delim)
// {
// 	while (*state->current)
// 	{
// 		handle_quotes(state);
// 		if (ft_strchr(delim, *state->current) && !state->in_single_quote
// 			&& !state->in_double_quote)
// 			break ;
// 		state->current++;
// 	}
// 	return (state->current);
// }

// char	*ft_strtok(char *line, const char *delim, t_parse *state)
// {
// 	char	*start;

// 	if (line)
// 	{
// 		state->current = line;
// 		state->in_single_quote = 0;
// 		state->in_double_quote = 0;
// 	}
// 	if (!state->current)
// 		return (NULL);
// 	skip_delim(state, delim);
// 	if (*state->current == '\0')
// 		return (NULL);
// 	start = state->current;
// 	state->current = process_token(state, delim);
// 	if (*state->current == '\0' && (state->in_single_quote
// 			|| state->in_double_quote))
// 		return (ft_putstr_fd("Error: Unclosed quote detected.\n", 2), NULL);
// 	if (*state->current)
// 	{
// 		*state->current = '\0';
// 		state->current++;
// 	}
// 	return (start);
// }
