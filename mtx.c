#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		printf("Token %d: %s\n", i, tokens[i]);
		i++;
	}
}

int	count_lines(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	**matrix_join(char **mtx1, char **mtx2)
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
	while (mtx1[i])
		matrix[j++] = strdup(mtx1[i++]);
	matrix[j] = "|";
	i = 0;
    j++;
	while (mtx2[i])
		matrix[j++] = strdup(mtx2[i++]);
	matrix[j] = NULL;
	return (matrix);
}


int	main(void)
{
	char	**matrix;

	char	*m1[] = {"alia", "dinis", NULL};
	char	*m2[] = {"alberto", "hamuyela", NULL};
	print_tokens(m1);
	printf("-------------------\n");
	print_tokens(m2);
	printf("-------------------\n");
	matrix = matrix_join(m1, m2);
	print_tokens(matrix);
	return (0);
}
