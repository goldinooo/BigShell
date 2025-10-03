#include "exp.h"
#include "minishell.h"
#include "lib.h"
#include <stdlib.h>
#include <unistd.h>

static int check_n_flag(char *str)
{
	int idx;

	if(str[0] != '-' || str[1] != 'n')
		return (0);
	idx = 2;
	while (str[idx])
	{
		if (str[idx] != 'n')
			return (0);
		idx++;
	}
	return (1);
}

void ex_echo(t_shell *shell, char **args)
{
	int idx;
	int print_nl;

	idx = 1;
	print_nl = 1;
	while (args[idx] && check_n_flag(args[idx]))
	{
		print_nl = 0;
		idx++;
	}
	while(args[idx])
	{
		ft_putstr_fd(args[idx], 1);
		if(args[idx + 1])
			ft_putstr_fd(" ", 1);
		idx++;
	}
	if (print_nl)
		ft_putstr_fd("\n", 1);
	shell->exit_status = EXIT_SUCCESS;
}
