#include "../includes/minishell.h"

int	handle_redir(char **args, int *saved_stdout, int *saved_stdin)
{
	int		i;
	int		fd;
	int		pipefd[2];
	char	*line;
	char	*delim;

	i = 0;
	*saved_stdout = dup(STDOUT_FILENO);
	*saved_stdin = dup(STDIN_FILENO);
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0)
		{
			if (ft_strcmp(args[i], ">") == 0)
				fd = open(args[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				fd = open(args[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
			{
				perror("open");
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
			args[i] = NULL;
		}
		else if (ft_strcmp(args[i], "<") == 0)
		{
			fd = open(args[i + 1], O_RDONLY);
			if (fd < 0)
			{
				perror("open");
				return (-1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
			args[i] = NULL;
		}
		else if (!ft_strcmp(args[i], "<<"))
		{
			delim = args[i + 1];
			pipe(pipefd);
			write(STDOUT_FILENO, "Here doc\n", 9);
			while (1)
			{
				line = readline("> ");
				if (!line || !ft_strcmp(line, delim))
					break ;
				write(pipefd[1], line, ft_strlen(line));
				write(pipefd[1], "\n", 1);
				free(line);
			}
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			args[i] = NULL;
		}
		i++;
	}
	return (0);
}
