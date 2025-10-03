#ifndef EXEC_H
#define EXEC_H

#include "env.h"
#include "exp.h"
#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//builtins
typedef struct s_shell	t_shell;


void	ex_cd(t_shell *shell, char **args);
void 	ex_echo(t_shell *shell, char **args);
void 	ex_env(t_shell *shell);
void 	ex_pwd(t_shell *shell);
void 	ft_unset(t_shell *shell, char **args);

void	ex_export(t_shell *shell, char *argv[]);

bool	is_faulty_redir(t_redir *redir);

// execution
void 	execute(t_shell *shell);


#endif