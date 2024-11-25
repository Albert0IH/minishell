/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:11:09 by ahamuyel          #+#    #+#             */
/*   Updated: 2024/11/25 11:19:33 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char buffer[BUFFER_SIZE];
	int bytes_read;

	while (1)
	{
		write(1, "minishell> ", 11);
		bytes_read = read(0, buffer, BUFFER_SIZE - 1);
		if (bytes_read == -1)
		{
			perror("Failed to read the input");
			exit(EXIT_FAILURE);
		}
		buffer[bytes_read - 1] = '\0';
		printf("%s\n", buffer);
	}
	return (0);
}
