/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_man3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retahri <retahri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 00:54:00 by retahri           #+#    #+#             */
/*   Updated: 2025/10/10 03:12:02 by retahri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static size_t	count_words(const char *str, char c)
{
	size_t	counter;

	counter = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str && *str != c)
			counter++;
		while (*str && *str != c)
			str++;
	}
	return (counter);
}

static void	*ft_free(char **strs, size_t count)
{
	while (count)
		free(strs[count--]);
	free(strs);
	return (NULL);
}

static size_t	get_word_len(const char *str, char c)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	idx;
	char	*str;

	idx = 0;
	if (!s || len == 0)
		return (ft_strdup(""));
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str = malloc(len + 1);
	if (!str)
		return (ft_strdup(""));
	while (s[start] && idx < len)
	{
		str[idx] = s[start];
		idx++;
		start++;
	}
	str[idx] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	idx;

	idx = 0;
	if (!s)
		return (NULL);
	arr = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			arr[idx] = ft_substr(s, 0, get_word_len(s, c));
			if (!arr[idx++])
				return (ft_free(arr, idx - 1));
		}
		while (*s && *s != c)
			s++;
	}
	arr[idx] = NULL;
	return (arr);
}
