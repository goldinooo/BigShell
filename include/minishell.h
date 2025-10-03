
#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

#include "utils.h"
#include "env.h"
#include "parsing.h"
#include "heredoc.h"

#define	SIG_KILLED 130

extern char **environ;


typedef struct s_shell
{
	t_env	*env;
	t_cmd	*cmd;
	int		exit_status;
}	t_shell;


/*
	Signals
*/
void	init_main_signals(void);
void	ignore_main_sigint(void);


#endif