#include "utils.h"

size_t	ft_strlen(const char *s)
{
	size_t	idx;

	if (!s || !*s)
		return (0);
	idx = 0;
	while (s[idx] != '\0')
		idx++;
	return (idx);
}
