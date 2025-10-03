#include "utils.h"

static char	*ft_before(char *str)
{
	size_t	i;
	size_t	len;
	char	*ptr;

	if (!str || str[0] == '\0')
		return (NULL);
	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		ptr = malloc(sizeof(char) * (len + 2));
	else
		ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = str[i];
		i++;
	}
	if (str[len] == '\n')
		ptr[i++] = '\n';
	ptr[i] = '\0';
	return (ptr);
}

static char	*ft_after(char *str)
{
	size_t	len;
	size_t	index;
	char	*ptr;

	if (!str)
		return (NULL);
	index = 0;
	while (str[index] && str[index] != '\n')
		index++;
	if (str[index] == '\0')
		return (free(str), NULL);
	len = 0;
	while (str[index + len + 1])
		len++;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (free(str), NULL);
	index++;
	len = 0;
	while (str[index])
		ptr[len++] = str[index++];
	ptr[len] = '\0';
	return (free(str), ptr);
}

static int	ft_newline(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

static char	*ft_read(int fd, char *buf, char *tmp, char *str)
{
	int	bytesread;

	bytesread = 1;
	while (bytesread > 0)
	{
		bytesread = read(fd, buf, BUFFER_SIZE);
		if (bytesread == -1)
			return (free(str), NULL);
		buf[bytesread] = '\0';
		if (!str)
		{
			str = malloc(sizeof(char) * 1);
			if (!str)
				break ;
			str[0] = '\0';
		}
		tmp = str;
		str = ft_strjoin(str, buf);
		free(tmp);
		if (!str)
			break ;
		if (ft_newline(str) == 1)
			break ;
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buf;
	char		*line;
	char		*tmp;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = NULL;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free(str), str = NULL, NULL);
	str = ft_read(fd, buf, tmp, str);
	free(buf);
	if (!str)
		return (NULL);
	line = ft_before(str);
	if (!line)
		return (free(str), str = NULL, NULL);
	str = ft_after(str);
	return (line);
}