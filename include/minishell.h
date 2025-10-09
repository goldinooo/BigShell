
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

#include "lib.h"
#include "env.h"
#include "parsing.h"
#include "heredoc.h"
#include "exec.h"
#include "utils.h"

#define EXIT_SIGNAL 128
#define	SIG_KILLED 130
#define EXIT_SYNTAX 2
#define SHELL_NAME "Minishell"
#define PREFIX "Minishell: cd: "
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


/*
	Clean Quotes: utils/clean_quotes.c
*/
bool	clean_quotes(t_cmd *cmd);

/*
	Clean Quotes: utils/exp_unst_utils.c
*/
int is_valid_id(char *str);
void print_any(char **cmd, t_shell *shell);
void ll(char **args, t_shell *shell);

/*
	Errors
*/
void	bprint_err(char *msg);

#endif