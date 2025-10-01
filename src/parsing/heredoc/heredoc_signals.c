#include "heredoc.h"
#include "utils.h"
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>


void handle_hd_sigint(int signum)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	exit(signum + EXIT_SIG);
}


void	ignore_sigint(void)
{
	struct sigaction	sa;
	sa.sa_handler(SIG_IGN);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa,NULL);
}

void setup_heredoc_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = handle_hd_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
}