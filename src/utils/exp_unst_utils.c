#include "minishell.h"
#include "lib.h"

int is_valid_id(char *str)
{
	int idx;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	idx = 1;
	while(str[idx])
	{
		if (!ft_isalnum(str[idx]) && str[idx] != '_') //"1VAR" invalid
			return (0);
		idx++;
	}
	return (1);
}