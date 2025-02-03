#include "includes/minishell.h"

void	update_env_var(char *line, char *var_name, char *var_value,
		char ***environ)
{
	int		i;
	char	*new_var;
	int		len;

	len = strlen(var_name);
	i = 0;
	while ((*environ)[i])
	{
		if (!strncmp((*environ)[i], var_name, len) && ((*environ)[i][len] == '='
				|| (*environ)[i][len] == '\0'))
		{
			new_var = create_env_var(line, var_name, var_value);
			if (!new_var)
				return ;
			free((*environ)[i]);
			(*environ)[i] = new_var;
			return ;
		}
		i++;
	}
}

void	update_env_var(char *line, char *var_name, char *var_value,
		char ***environ)
{
}

int	main(int ac, char **av)
{
	(void)ac;
}
