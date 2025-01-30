/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:52:13 by ahamuyel          #+#    #+#             */
/*   Updated: 2025/01/30 14:27:54 by ahamuyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sig_on_cat(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\nminishell> ", 1);
	else if (sig == SIGQUIT)
	{
	}
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
