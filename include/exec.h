#ifndef EXEC_H
#define EXEC_H

#include "env.h"
#include "exp.h"
#include "lib.h"
#include "parsing.h"
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

// redir
bool	is_faulty_redir(t_redir *redir);
bool	init_redirection(t_cmd *cmd);
bool	redir_in(t_redir *redir);
bool	redir_out(t_redir *redir);

// execution
void 	execute(t_shell *shell);
int		is_builtin(char *cmd);
void	exec_builtin(t_shell *shell, char **args);
void	child_proc(t_shell *shell, int st, t_cmd *cmd, char **envp, char *bp);



// pipe
bool	setup_with_backup(t_cmd *cmd, int *save_stdout, int *save_stdin);
void	reset_and_catch_sig(t_shell *shell, int status, bool toggle);
void	setup_io(t_cmd *cmd, int prev_fd, int pipedes[2]);
void	ex_child(t_shell *shell, t_cmd *cmd, int prev_fd, int pipedes[2]);
bool	cmd_redir_output(t_cmd *cmd);
void	ex_pipe(t_shell *shell, int prev_fd, pid_t pid);


// find_binary
char	*get_bin_path(char *bin, t_env *env);

/*
	./exec/redirs/redirs.c
*/
bool	init_redirection(t_cmd *cmd);


#endif