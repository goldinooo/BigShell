#include "utils.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	idx;
	size_t	srcsize;

	srcsize = ft_strlen(src);
	if (!dst || !dstsize)
		return (srcsize + dstsize);
	idx = 0;
	while (src[idx] != '\0' && idx < dstsize - 1)
	{
		*dst++ = src[idx];
		idx++;
	}
	*dst = '\0';
	return (srcsize);
}
