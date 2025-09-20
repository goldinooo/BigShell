#include "../../minishell.h"

size_t get_len(char *s)
{
	int idx = 0;
	while (s[idx])
		idx++;
	return(idx);
}


size_t croplen(char *s, char to_cut)
{
	int idx = 0;

	idx = 0;
	while (s[idx])
	{
		if (s[idx] == to_cut)
			return (idx);
		idx++;
	}
	return (0);
}
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	idx;
	char	*str;

	idx = 0;
	if (!s || len == 0)
		return (NULL);
	if (start >= get_len(s))
		return (NULL);
	if (len > get_len(s) - start)
		len = get_len(s) - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (s[start] && idx < len)
	{
		str[idx] = s[start];
		idx++;
		start++;
	}
	str[idx] = '\0';
	return (str);
}