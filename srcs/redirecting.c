#include "../includes/minishell.h"

int handle_redir(char **args, int *saved_stdout, int *saved_stdin)
{
    // int i;
    // int fd;

    // i = 0;
    // while (args[i])
    // {
    //     if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], ">>"))
    //     {
    //         if (!ft_strcmp(args[i], ">"))
    //             fd = open(args[i + 1], O_CREAT | O_RDONLY | O_TRUNC, 0644);
    //         else
    //             fd = open(args[i + 1], O_CREAT | O_RDONLY | O_APPEND, 0644);
    //         if (fd < 0)
    //         {
    //             ft_putstr_fd("ERROR: open\n", STDERR_FILENO);
    //             return (-1);
    //         }
    //         dup2(fd, STDOUT_FILENO);
    //         close(fd);
    //         args[i] = NULL;
    //     }
    //     i++;
    // }
    // return (0);
    int	i;
	int	fd;

	i = 0;
	*saved_stdout = dup(STDOUT_FILENO); // Salva o descritor de saída
	*saved_stdin = dup(STDIN_FILENO);   // Salva o descritor de entrada

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
			dup2(fd, STDOUT_FILENO); // Redireciona saída para o arquivo
			close(fd);
			args[i] = NULL; // Remove redirecionamento dos argumentos
		}
		else if (ft_strcmp(args[i], "<") == 0)
		{
			fd = open(args[i + 1], O_RDONLY);
			if (fd < 0)
			{
				perror("open");
				return (-1);
			}
			dup2(fd, STDIN_FILENO); // Redireciona entrada do arquivo
			close(fd);
			args[i] = NULL; // Remove redirecionamento dos argumentos
		}
		i++;
	}
	return (0);
}