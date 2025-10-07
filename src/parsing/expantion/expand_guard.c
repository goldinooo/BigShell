#include "exp.h"
#include "lexer.h"
#include "parsing.h"
#include "lib.h"
#include <stdlib.h>

bool multiple_args(char *value, bool space, bool squotes, bool dquotes)
{
	int idx;

	idx = 0;
	while(value[idx])
	{
		if (space && !squotes && !dquotes)
			return (true);
		else
		{
			if (is_space(value[idx]))
				space = true;
			if (value[idx] == SQUOTE && !dquotes)
				squotes = !squotes;
			else if (value[idx] == DQUOTE && !squotes)
				dquotes = !dquotes;
		}
		idx++;
	}
	return (false);
}

char **append_args(char **args, char *value, int *pos, int sub)
{
	int idx;
	int len;
	char **new;
	char **buf;

	idx = 0;
	buf = ft_split(value, ' ');
	len = args_len(args) + args_len(buf);
	new = (char **)malloc((len + 1) * sizeof(char *));
	while (idx < *pos)
		(new[idx] = ft_strdup(args[idx]), free(args[idx++]));
	while (buf[sub])
		new[idx++] = ft_strdup(buf[sub++]);
	sub = *pos + 1;
	while(args[sub])
	{
		new[idx++] = ft_strdup(args[sub]);
		free(args[sub]);
		sub++;
	}
	new[idx] = NULL;
	*pos += (args_len(buf) - 1);
	return (free(value), free(args), clr_char_array(buf), new);
}
