#include "env.h"
#include "exp.h"
#include "minishell.h"
#include "lib.h"
#include <stdlib.h>
#include <unistd.h>


void	ex_cd(t_shell *shell, char **args)
{
	char *target;

	target = NULL;
	shell->exit_status = EXIT_SUCCESS;
	target = value_from_env(ft_strdup("HOME"), shell->env);
	if (!target)
	{
		print_error_fd("HOME not found wla chi 9alwa", shell);
		return;
	}
	if(!args[1] || (args[1] && !args[1][0])) // cd alone
	{
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
		print_any(args);
		// print_perror ("cd makhadamachi wla chi 9alwaaaaaaaaaa", shell);
		
}
