
#include "../includes/minishell.h"

void	free_args(char **array)
{
	int	i;

	i = 0;
	if (array != NULL)
	{
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

char	*get_command_path(char *cmd)
{
	char	*dir;
	char	*full_path;
	char	*tmp;
	char	**directories;
	int		i;
	char	*path;

	i = 0;
	path = getenv("PATH");
	if (path == NULL)
		return (NULL);
	if (cmd[0] == '/')
		return (cmd);
	directories = ft_split(path, ':');
	while (directories[i])
	{
		dir = directories[i];
		tmp = ft_strjoin(dir, "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, F_OK) == 0)
		{
			free_args(directories);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_args(directories);
	return (NULL);
}

void split_pipes(char *input, char **cmd)
{
	int i;
	char *token;

	i = 0;
	token = my_strtok(input, "|");
	while (token)
	{
		cmd[i] = token;
		token = my_strtok(NULL, "|");
		i++;	
	}
	cmd[i] = NULL;
}

int	handle_redirections(char **args, int *saved_stdout, int *saved_stdin)
{
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


void	execute_pipeline(char **commands)
{
	int		i = 0, fd[2], in_fd = 0;
	pid_t	pid;

	while (commands[i])
	{
		if (commands[i + 1] && pipe(fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid ==-1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (in_fd != 0) // Conectar entrada ao pipe anterior
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (commands[i + 1]) // Conectar saída ao próximo pipe
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			execute_command(commands[i]);
		}
		else
		{
			wait(NULL);
			if (in_fd != 0)
				close(in_fd);
			if (commands[i + 1])
				in_fd = fd[0];
			close(fd[1]);
		}
		i++;
	}
}
