#include "exec.h"
#include "minishell.h"

void print_error_fd(char *str, t_shell *shell)
{
	ft_putstr_fd(str, STDERR_FILENO);
	shell->exit_status = EXIT_FAILURE;
}

void print_perror(char *str, t_shell *shell)
{
	perror(str);
	shell->exit_status = EXIT_FAILURE;
}
void exit_with_status(t_shell *shell, int status)
{
	shell->exit_status = status;
	exit(status);
}