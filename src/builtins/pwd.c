#include "minishell.h"
#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void ex_pwd(t_shell *shell)
{
	char cwd[1024];

	if(getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
		shell->exit_status = EXIT_SUCCESS;
	}
	else
	{
		perror("invalid pwd behavior");
		shell->exit_status = EXIT_SUCCESS;
	}
}