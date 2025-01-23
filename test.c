#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char	*ft_get_env(char *name, char **environ)
{
	int		i;
	size_t	name_len;

	if (!name || !environ)
		return (NULL);
	name_len = strlen(name);
	i = 0;
	while (environ[i])
	{
		if (!strncmp(environ[i], name, name_len) && environ[i][name_len] == '=')
			return (environ[i] + name_len + 1);
		i++;
	}
	return (NULL);
}
int	main(int ac, char **av, char **environ)
{
	char	*value;

	(void)ac;
	(void)av;
	value = ft_get_env("PATH", environ);
	if (value)
		printf("PATH: %s\n", value);
	else
		printf("Variable not found.\n");
	return (0);
}
