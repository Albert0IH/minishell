/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:56:44 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/25 07:10:01 by ahamuyel         ###   ########.fr       */
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
	new_input = malloc(sizeof(char *) * ((count_operator(input) + 2) + 1));
	while (input[i])
	{
		if (is_operator(input[i]) && input[i + 1])
		{
			new_input[j] = ft_strdup(input[i]);
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
	while (mop[i])
		lexic_tokens[j++] = ft_strdup(mop[i++]);
	lexic_tokens[j] = NULL;
	free_args(mop);
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
		matrix[j] = "|";
	i = 0;
	while (mtx2 && mtx2[i])
		matrix[j++] = ft_strdup(mtx2[i++]);
	matrix[j] = NULL;
	free_args(mtx1);
	return (matrix);
}

char	**mult_lexic_sort(char **input)
{
	int		i;
	int		j;
	char	**final;
	char	**sorted;
	char	**tmp;

	i = 0;
	j = 0;
	final = NULL;
	sorted = NULL;
	tmp = malloc(sizeof(char *) * (count_lines(input) + 1));
	while (input[i])
	{
		if (!ft_strcmp(input[i], "|"))
		{
			tmp[j] = NULL;
			sorted = sort_lexic(tmp);
			final = matrix_join(final, sorted, 1);
			free_tokens(tmp);
			free_args(sorted);
			j = 0;
		}
		tmp[j] = ft_strdup(input[i]);
		i++;
		j++;
	}
	tmp[j] = NULL;
	sorted = sort_lexic(tmp);
	final = matrix_join(final, sorted, 0);
	free_args(tmp);
	free_args(sorted);
	return (final);
}