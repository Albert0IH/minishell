#include "../includes/minishell.h"


int	count_lines(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	**ft_environ(char **environ)
{
	char	**env;
	int		i;
	int		len;

	env = malloc(sizeof(char *) * (count_lines(environ) + 1));
	i = 0;
	while (environ[i])
	{
		len = strlen(environ[i]);
		env[i] = malloc(sizeof(char) * (len + 1));
		strcpy(env[i], environ[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}


int	main(int ac, char **av, char **environ)
{
	char	*line;
	char	*commands[100];
	char	**env;

	(void)av;
	(void)ac;
	env = ft_environ(environ);
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
		{
			free(line);
			continue ;
		}
		if (*line)
			add_history(line);
		split_pipes(line, commands);
		execute(commands, env);
		free(line);
	}
	free_args(env);
	return (0);
}
