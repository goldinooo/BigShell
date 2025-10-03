#ifndef HEREDOC_H
#define HEREDOC_H

#include "exp.h"

typedef struct s_shell	t_shell;
typedef struct s_redir	t_redir;

#define EXIT_SIG 30
#define TMP_HD "/tmp/.doctorishere.tmp"

void	ignore_main_sigint(void);
bool	should_heredoc_expand(t_redir *redir);

char	*expand_heredoc(t_shell *shell, char *line);

/*
	Heredoc signals
*/
void 	init_heredoc_signals(void);

#endif