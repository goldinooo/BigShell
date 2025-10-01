#include "lexer.h"
#include <stdbool.h>

bool	is_pipe(char ch)
{
	return (ch == PIPE);
}

bool	is_op(char ch)
{
	return (is_pipe(ch) || ch == REDIR_IN || ch == REDIR_OUT);
}

bool	is_redir(char ch, int dir)
{
	if (dir == 0) // input redirection
		return (ch == REDIR_IN);
	else if (dir == 1) // output redirection
		return (ch == REDIR_OUT);
	return (false);
}
