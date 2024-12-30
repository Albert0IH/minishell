#include "../includes/minishell.h"

int	main(void)
{
	char	*input;

	char *commands[10]; // Para até 10 comandos separados por pipe
	while (1)
	{
		input = readline("minishell> ");
		if (!input || ft_strncmp(input, "exit", 5) == 0)
		{
			free(input);
			break ;
		}
		if (*input)
			add_history(input);
		split_pipes(input, commands);
		if (commands[1] == NULL) // Comando único
		{
			if (fork() == 0)
				execute_command(commands[0]);
			wait(NULL);
		}
		else // Pipeline
		{
			execute_pipeline(commands);
		}
		free(input);
	}
	rl_clear_history();
	return (0);
}
