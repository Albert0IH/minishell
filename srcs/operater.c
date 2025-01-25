/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operater.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinis <adinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:38:02 by adinis            #+#    #+#             */
/*   Updated: 2025/01/25 11:56:20 by adinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_operator(char *s)
{
	if (!ft_strcmp(s, ">") || !ft_strcmp(s, ">>") || !ft_strcmp(s, "<")
		|| !ft_strcmp(s, "<<"))
		return (1);
	return (0);
}

int	count_operator(char **s)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (is_operator(s[i]))
			count++;
		i++;
	}
	return (count);
}

char	**operator_matrix(char **input)
{
	int		i;
	int		j;
	char	**new_input;

	i = 0;
	j = 0;
	new_input = malloc(sizeof(char *) * ((count_operator(input) * 2) + 1));
	while (input[i])
	{
		if (is_operator(input[i]) && input[i + 1])
		{
			new_input[j] = ft_strdup(input[i]);
			if (!new_input[j])
				return (free_args(new_input), NULL);
			new_input[j + 1] = ft_strdup(input[i + 1]);
			i += 2;
			j += 2;
			continue ;
		}
		i++;
	}
	new_input[j] = NULL;
	return (new_input);
}
