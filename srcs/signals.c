#include "../includes/minishell.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\nminishell> ", 1);
	else if (sig == SIGQUIT)
	{}
}

void	setup_signals(void)
{
	struct sigaction sa;
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
