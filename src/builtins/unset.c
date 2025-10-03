#include "exp.h"
#include "minishell.h"
#include <stdarg.h>









static void unset_var(char **args, t_shell *shell)
{
	
}




void ft_unset(t_shell *shell, char **args)
{
	int idx;

	if (!args || !args[1] || !shell || !shell->env)
		return;
	idx = 1;
	while(args[idx])
	{

		idx++;
	}
}