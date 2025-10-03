#include "env.h"
#include "exp.h"
#include "minishell.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


static void print_error_fd(char *str, t_shell *shell)
{
	ft_putstr_fd(str, STDERR_FILENO);
	shell->exit_status = EXIT_FAILURE;
}

static void print_perror(char *str, t_shell *shell)
{
	perror(str);
	shell->exit_status = EXIT_FAILURE;
}

void	ex_cd(t_shell *shell, char **args)
{
	char *target;

	target = NULL;
	shell->exit_status = EXIT_SUCCESS;
	if(!args[1]) // cd alone
	{
		target = value_from_env("HOME", shell->env);
		if (!target)
		{
			print_error_fd("HOME not found wla chi 9alwa", shell);
			return;
		}
		if (chdir(target) != 0)
			print_perror("cd makhadamachi wla chi 9alwa", shell);
		return;
	}
	if (args[2])
	{
		print_error_fd("bzzf d args a khawa wla chi 9alwa", shell);
		return;
	}
	if (chdir(args[1]) != 0)
		print_perror("cd makhadamachi wla chi 9alwa", shell);
}
