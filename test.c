#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void	print_tokens(char **tokens)
// {
// 	int	i;

// 	i = 0;
// 	while (tokens[i])
// 	{
// 		printf("Token %d: %s\n", i, tokens[i]);
// 		free(tokens[i]);
// 		i++;
// 	}
// }
// int	count_lines(char **s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// char	**ft_environ(char **environ)
// {
// 	char	**env;
// 	int		i;
// 	int		len;

// 	env = malloc(sizeof(char *) * (count_lines(environ) + 1));
// 	i = 0;
// 	while (environ[i])
// 	{
// 		len = strlen(environ[i]);
// 		env[i] = malloc(sizeof(char) * (len + 1));
// 		strcpy(env[i], environ[i]);
// 		i++;
// 	}
// 	env[i] = NULL;
// 	return (env);
// }

// char	*ft_get_env(char *name, char **environ)
// {
// 	int		i;
// 	size_t	name_len;

// 	if (!name || !environ)
// 		return (NULL);
// 	name_len = strlen(name);
// 	i = 0;
// 	while (environ[i])
// 	{
// 		if (!strncmp(environ[i], name, name_len) && environ[i][name_len] == '=')
// 			return (environ[i] + name_len + 1);
// 		i++;
// 	}
// 	return (NULL);
// }

// // int	main(int ac, char **av, char **environ)
// // {
// // 	char	*value;

// // 	(void)ac;
// // 	(void)av;
// // 	value = ft_get_env("PATH", environ);
// // 	if (value)
// // 		printf("PATH: %s\n", value);
// // 	else
// // 		printf("Variable not found.\n");
// // 	return (0);
// // }

// void	sort_lexic(char **av)
// {
// 	char	*cmd;
// 	char	*oprd;
// 	char	*file;

// 	cmd = av[3];
// 	oprd = av[1];
// 	file = av[2];

// 	av[1] = cmd;
// 	av[2] = oprd;
// 	av[3] = file;
// }

// int	main(int ac , char **av)
// {
// 	(void)ac;
// 	int		i;
// 	sort_lexic(av);
// 	i = 1;
// 	while (av[i])
// 	{
// 		printf("Token %d: %s\n", i, av[i]);
// 		i++;
// 	}
// 	return (0);
// }

// // int	check_readline(char *line)
// // {
// // 	int	i;

// // 	i = 0;
// // 	while (line != ' ')
// // 		i++;
// // 	if (line == '\0');
// // 		return (0);
// // 	return (1);
// // }

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;
	size_t	total_len;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	total_len = strlen(s1) + strlen(s2);
	result = (char *)malloc((total_len * sizeof(char)) + 1);
	if (result == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		result[i] = ((unsigned char *)s1)[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		result[i++] = ((unsigned char *)s2)[j++];
	result[i] = '\0';
	return (result);
}

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

int	is_operator(char *s)
{
	if (!strcmp(s, ">") || !strcmp(s, ">>") || !strcmp(s, "<") || !strcmp(s,
			"<<"))
		return (1);
	return (0);
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
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
			new_input[j] = strdup(input[i]);
			new_input[j + 1] = strdup(input[i + 1]);
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
		if (!strcmp(array[i], s))
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
			lexic_tokens[j] = strdup(av[i]);
		i++;
		j++;
	}
	i = 0;
	while (mop[i])
		lexic_tokens[j++] = mop[i++];
	lexic_tokens[j] = NULL;
	return (lexic_tokens);
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
	while (mtx1 && mtx1[i])
		matrix[j++] = strdup(mtx1[i++]);
	matrix[j] = "|";
	i = 0;
	// j++;
	while (mtx2[i])
		matrix[j++] = strdup(mtx2[i++]);
	matrix[j] = NULL;
	return (matrix);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
			free(args[i++]);
		free(args);
	}
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
		if (!strcmp(input[i], "|"))
		{
			tmp[j] = NULL;
			sorted = sort_lexic(tmp);
			// printf("...............\n");
			// print_tokens(sorted);
			// //printf("...............\n");
			final = matrix_join(final, sorted);
			free_tokens(tmp);
			free_args(sorted);
			j = 0;
		}
		tmp[j] = strdup(input[i]);
		i++;
		j++;
	}
	tmp[j] = NULL;
	sorted = sort_lexic(tmp);
	final = matrix_join(final, sorted);
	free_args(tmp);
	free_args(sorted);
	return (final);
}

int	main(int ac, char **av)
{
	char	**lexic;

	(void)ac;
	print_tokens(av);
	printf("---------- ordenado ---------\n");
	lexic = mult_lexic_sort(av + 1);
	print_tokens(lexic);
	return (0);
}

// int	main(void)
// {
// 	char	**matrix;
// 	char	**m1;
// 	char	**m2;

// 	m1 = {"alia", "dinis", NULL};
// 	m2 = {"alberto", "hamuyela", NULL};
// 	print_tokens(m1);
// 	printf("-------------------\n");
// 	print_tokens(m2);
// 	printf("-------------------\n");
// 	matrix = matrix_join(m1, m2);
// 	print_tokens(matrix);
// 	return (0);
// }
