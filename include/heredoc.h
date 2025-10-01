#ifndef HEREDOC_H
#define HEREDOC_H

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "utils.h"
#include <sys/wait.h>

#define EXIT_SIG 30
#define TMP_HD "path" //! todo "/tmp/.minishell_heredoc.tmp"

void	ignore_sigint(void);
void	ignore_sigint(void);
void 	setup_heredoc_signals(void);

#endif