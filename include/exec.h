#ifndef EXEC_H
#define EXEC_H

#include "env.h"
#include "exp.h"
#include "lib.h"
#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//builtins
typedef struct s_shell	t_shell;
typedef struct s_cmd	t_cmd;


void	ex_cd(t_shell *shell, char **args);
void 	ex_echo(t_shell *shell, char **args);
void 	ex_env(t_shell *shell);
void 	ex_pwd(t_shell *shell);
void 	ex_unset(t_shell *shell, char **args);
void 	ex_exit(t_shell *shell, char **args);
void	ex_export(t_shell *shell, char *argv[]);

bool	is_faulty_redir(t_redir *redir);
bool	init_redirection(t_cmd *cmd);
bool	redir_in(t_redir *redir);
bool	redir_out(t_redir *redir);

// execution
void 	execute(t_shell *shell);
int		is_builtin(char *cmd);
void	exec_builtin(t_shell *shell, char **args);


#endif