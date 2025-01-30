/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:25:09 by adinis            #+#    #+#             */
/*   Updated: 2025/01/30 12:37:43 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_in(char **args, int fd, int i)
{
	if (ft_strcmp(args[i], ">") == 0)
		fd = open(args[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(args[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	free(args[i]);
	args[i] = NULL;
	free(args[i + 1]);
	args[i + 1] = NULL;
	i++;
}

void	redir_out(char **args, int fd, int i)
{
	if (fd < 0)
	{
		perror("open");
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	free(args[i]);
	args[i] = NULL;
	free(args[i + 1]);
	args[i + 1] = NULL;
	i++;
}

void	here_doc(char **args, int i, char *delim, int pipefd[2])
{
	char	*line;

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
	free(args[i]);
	args[i] = NULL;
	free(args[i + 1]);
	args[i + 1] = NULL;
	i++;
}

int	handle_redir(char **args, int *saved_stdout, int *saved_stdin)
{
	int		i;
	int		fd;
	int		pipefd[2];
	char	*delim;

	i = 0;
	*saved_stdout = dup(STDOUT_FILENO);
	*saved_stdin = dup(STDIN_FILENO);
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0)
			redir_in(args, fd, i);
		else if (ft_strcmp(args[i], "<") == 0)
		{
			fd = open(args[i + 1], O_RDONLY);
			redir_out(args, fd, i);
		}
		else if (!ft_strcmp(args[i], "<<"))
		{
			delim = args[i + 1];
			here_doc(args, i, delim, pipefd);
		}
		i++;
	}
	return (0);
}
