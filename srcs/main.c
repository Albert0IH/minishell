#include "../includes/minishell.h"

int	main(int ac, char **av, char **environ)
{
	(void)av;
	(void)ac;
	(void)environ;
	char *line;
	char *commands[100];
	//int i = 0;

	setup_signals();
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (!ft_strcmp(line, "\0"))
			continue;
		if (*line)
			add_history(line);
		split_pipes(line, commands);
		execute(commands, environ);
		// tokenize_line(line, commands);
		// print_tokens(commands);
		free(line);
	}
	return (0);
}
