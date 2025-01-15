#include "../includes/minishell.h"

int	main(int ac, char **av, char **environ)
{
	(void)av;
	(void)ac;
	char *line;
	char *commands[100];

	setup_signals();
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			free(line);
			break ;
		}
		if (!ft_strcmp(line, "\0"))
			continue;
		if (*line)
			add_history(line);
		split_pipes(line, commands);
		execute(commands, environ);
		//free_tokkens(commands);
		free(line);
		line = NULL;
	}
	return (0);
}
