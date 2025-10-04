#ifndef EXEC_H
#define EXEC_H

#include "env.h"
#include "exp.h"
#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_shell	t_shell;
typedef struct s_cmd	t_cmd;

//builtins
void	ex_cd(t_shell *shell, char **args);
void 	ex_echo(t_shell *shell, char **args);
void 	ex_env(t_shell *shell);
void 	ex_pwd(t_shell *shell);
void 	ex_unset(t_shell *shell, char **args);
void 	ex_exit(t_shell *shell, char **args);
void	ex_export(t_shell *shell, char *argv[]);

bool	is_faulty_redir(t_redir *redir);

// execution
void 	execute(t_shell *shell);

// find_binary
char	*get_bin_path(char *bin, t_env *env);

/*
	./exec/redirs/redirs.c
*/
bool	init_redirection(t_cmd *cmd);


#endif