#include "includes/minishell.h"

int	count_commands(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (line[i])
	{
		if (line[i] == '|')
			++count;
		i++;
	}
	return (count);
}

int	count_pipes(char *input)
{
	int		i;
	int		count;
	t_parse	states;

	states.in_single_quote = 0;
	states.in_double_quote = 0;
	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|' && (!states.in_single_quote
				|| !states.in_double_quote))
			count++;
		i++;
	}
	return (count + 1);
}

int	main(void)
{
	char	*line;

	line = "ls -l | grep minishell | wc -l";
	printf("%d\n", count_pipes(line));
	return (0);
}
