#include "minishell.h"

int args_len(char **args)
{
	int idx;

	idx = 0;
	while(args[idx])
		idx++;
	return (idx);
}