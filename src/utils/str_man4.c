#include "utils.h"

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	c = (unsigned char) c;
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *) s);
		s++;
	}
	if (c == '\0')
		return ((char *) s);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && i < n)
	{
		i++;
	}
	if (n == i)
		return (0);
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	else if (!s1 && s2)
		return (ft_strdup(s2));
	else if (s1 && !s2)
		return (ft_strdup(s1));
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	// free(s1); // TODO remove free
	return (str);
}

bool	is_space(char ch)
{
	return ((ch >= 9 && ch <= 13) || ch == 32);
}
