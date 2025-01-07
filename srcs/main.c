#include "../includes/minishell.h"

int	main(void)
{
	char *line;
	char *commands[100];

	setup_signals();
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		split_pipes(line, commands);
		execute(commands);
		free(line);
	}
	return (0);
}
