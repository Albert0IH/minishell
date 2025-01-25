/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinis <adinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:56:44 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/25 11:37:46 by adinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
