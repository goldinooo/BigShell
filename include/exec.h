#ifndef EXEC_H
#define EXEC_H

#include "env.h"
#include "exp.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//builtins
typedef struct s_shell	t_shell;


void	ex_cd(t_shell *shell, char **args);
void 	ex_echo(t_shell *shell, char **args);
void 	ex_env(t_shell *shell);
void 	ex_pwd(t_shell *shell);

// execution
void 	execute(t_shell *shell);


#endif