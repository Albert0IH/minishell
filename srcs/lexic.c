/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:56:44 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/02/04 13:39:55 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	matrix_copy(char **src, char **dst)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		i++;
	}
	dst[i] = NULL;
	free_args(src);
}

char	**sort_lexic(char **av)
{
	char	**lexic_tokens;
	char	**mop;
	int		i;
	int		j;

	lexic_tokens = malloc(sizeof(char *) * (count_lines(av) + 1));
	mop = operator_matrix(av);
	i = 0;
	j = 0;
	while (av[i])
	{
		if (is_operator(av[i]) && av[i + 1])
		{
			i += 2;
			continue ;
		}
		else
			lexic_tokens[j] = ft_strdup(av[i]);
		i++;
		j++;
	}
	i = 0;
	matrix_copy(mop, lexic_tokens + j);
	return (lexic_tokens);
}

char	**matrix_join(char **mtx1, char **mtx2, int pipe)
{
	char	**matrix;
	int		i;
	int		j;
	size_t	len_m1;
	size_t	len_m2;

	i = 0;
	j = 0;
	len_m1 = count_lines(mtx1);
	len_m2 = count_lines(mtx2);
	matrix = malloc(sizeof(char *) * (len_m1 + len_m2 + 2));
	while (mtx1 && mtx1[i])
		matrix[j++] = ft_strdup(mtx1[i++]);
	if (pipe && mtx1)
		matrix[j] = ft_strdup("|");
	i = 0;
	while (mtx2 && mtx2[i])
		matrix[j++] = ft_strdup(mtx2[i++]);
	matrix[j] = NULL;
	free_args(mtx1);
	return (matrix);
}

char	**mult_lexic_sort(char **input)
{
	char	**final;

	final = NULL;
	final = sort_lexic(input);
	return (final);
}
