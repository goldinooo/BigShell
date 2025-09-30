
#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
// # include <readline/readline.h>
// # include <readline/history.h>

#include "utils.h"
#include "env.h"

extern char **environ;


typedef struct s_shell
{
	t_env	*env;
	// TODO t_cmd struct;
}	t_shell;

#endif