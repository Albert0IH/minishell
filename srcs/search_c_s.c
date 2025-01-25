/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_c_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinis <adinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:47:23 by adinis            #+#    #+#             */
/*   Updated: 2025/01/25 12:44:36 by adinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_path(t_path *path_info)
{
	path_info->full_path = NULL;
	path_info->directories = NULL;
	path_info->environ = NULL;
}
void	init_token(t_token *s)
{
	s->parsed_token= NULL;
	s->input = NULL;
	s->expanded = NULL;
	s->word = NULL;
}
int	count_lines(char **s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_search_str(char **array, char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (array[i])
	{
		if (!ft_strcmp(array[i], s))
			count++;
		i++;
	}
	return (count);
}

int	ft_searc_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}
