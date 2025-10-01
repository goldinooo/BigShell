#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct s_redir
{
	char *file;
	int heredoc_fd;
	bool shouldexpand;
	size_t type;
	struct s_redir *next;
} t_redir;

typedef struct s_cmd
{
	char **args;
	t_redir *redir;
	struct s_cmd *next;
}	t_cmd;

#endif