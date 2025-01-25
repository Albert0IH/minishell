/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinis <adinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:25:09 by adinis            #+#    #+#             */
/*   Updated: 2025/01/25 11:25:11 by adinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			free(line);
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			args[i] = NULL;
		}
		i++;
	}
	return (0);
}

// #include "../includes/minishell.h"

// static int	redirect_output(char **args, int i)
// {
// 	int	fd;

// 	if (ft_strcmp(args[i], ">") == 0)
// 		fd = open(args[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	else
// 		fd = open(args[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		return (-1);
// 	}
// 	if (dup2(fd, STDOUT_FILENO) < 0)
// 	{
// 		perror("dup2");
// 		close(fd);
// 		return (-1);
// 	}
// 	close(fd);
// 	if (args[i])
// 	{
// 		free(args[i]);
// 		args[i] = NULL;
// 	}
// 	return (0);
// }
// // static int redirect_input(char **args, int i)
// // {
// //     int fd;

// //     fd = open(args[i + 1], O_RDONLY);
// //     if (fd < 0)
// //     {
// //         perror("open");
// //         return (-1);
// //     }
// //     if (dup2(fd, STDIN_FILENO) < 0)
// //     {
// //         perror("dup2");
// //         close(fd);
// //         return (-1);
// //     }
// //     close(fd);
// //     args[i] = NULL;
// //     return (0);
// // }

// // static int handle_heredoc(char **args, int i)
// // {
// //     int pipefd[2];
// //     char *line;
// //     char *delim;

// //     delim = args[i + 1];
// //     if (pipe(pipefd) < 0)
// //     {
// //         perror("pipe");
// //         return (-1);
// //     }
// //     write(STDOUT_FILENO, "Here doc\n", 9);
// //     while (1)
// //     {
// //         line = readline("> ");
// //         if (!line || !ft_strcmp(line, delim))
// //             break ;
// //         write(pipefd[1], line, ft_strlen(line));
// //         write(pipefd[1], "\n", 1);
// //         free(line);
// //     }
// //     free(line);
// //     close(pipefd[1]);
// //     if (dup2(pipefd[0], STDIN_FILENO) < 0)
// //     {
// //         perror("dup2");
// //         close(pipefd[0]);
// //         return (-1);
// //     }
// //     close(pipefd[0]);
// //     args[i] = NULL;
// //     return (0);
// // }

// int	handle_redir(char **args, int *saved_stdout, int *saved_stdin)
// {
// 	int	i;

// 	i = 0;
// 	*saved_stdout = dup(STDOUT_FILENO);
// 	*saved_stdin = dup(STDIN_FILENO);
// 	if (*saved_stdout < 0 || *saved_stdin < 0)
// 	{
// 		perror("dup");
// 		return (-1);
// 	}
// 	while (args[i])
// 	{
// 		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0)
// 		{
// 			if (redirect_output(args, i) < 0)
// 				return (-1);
// 		}
// 		// else if (ft_strcmp(args[i], "<") == 0)
// 		// {
// 		//     if (redirect_input(args, i) < 0)
// 		//         return (-1);
// 		// }
// 		// else if (!ft_strcmp(args[i], "<<"))
// 		// {
// 		//     if (handle_heredoc(args, i) < 0)
// 		//         return (-1);
// 		// }
// 		i++;
// 	}
// 	return (0);
// }
