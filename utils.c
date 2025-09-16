/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reda <reda@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:00:00 by reda              #+#    #+#             */
/*   Updated: 2025/09/16 00:00:00 by reda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

/*
 * Count words separated by delimiter
 * 
 * Helper function to determine how many strings we'll need to allocate
 * for the result array.
 */
static int	count_words(char const *s, char c)
{
	int		count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
		{
			in_word = 0;
		}
		s++;
	}
	return (count);
}

/*
 * Get length of next word
 * 
 * Calculates the length of the word starting at position s,
 * up to the next delimiter or end of string.
 */
static int	word_length(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

/*
 * Duplicate a portion of string
 * 
 * Creates a new string containing 'len' characters from 's'.
 * Similar to strdup but with length limit.
 */
static char	*ft_strndup(char const *s, int len)
{
	char	*dup;
	int		i;

	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/*
 * Free array of strings
 * 
 * Helper function to clean up in case of allocation failure.
 * Frees all previously allocated strings and the array itself.
 */
static void	free_split(char **split, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/*
 * Split string by delimiter
 * 
 * Takes a string and splits it into an array of strings using
 * the specified delimiter. Returns NULL-terminated array.
 * 
 * Example:
 * ft_split("hello world test", ' ') 
 * Returns: ["hello", "world", "test", NULL]
 * 
 * Memory management:
 * - Caller is responsible for freeing the returned array
 * - Each string in the array must be freed individually
 * - The array itself must also be freed
 */
char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	
	/* Count how many words we have */
	word_count = count_words(s, c);
	
	/* Allocate array for word_count + 1 (NULL terminator) */
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	
	i = 0;
	while (i < word_count)
	{
		/* Skip delimiters */
		while (*s == c)
			s++;
		
		/* Get length of current word */
		len = word_length(s, c);
		
		/* Duplicate the word */
		result[i] = ft_strndup(s, len);
		if (!result[i])
		{
			free_split(result, i);
			return (NULL);
		}
		
		/* Move to next word */
		s += len;
		i++;
	}
	
	/* NULL terminate the array */
	result[word_count] = NULL;
	return (result);
}

/*
 * Free the result of ft_split
 * 
 * Convenience function to properly free the array returned by ft_split.
 * Frees each string and then the array itself.
 */
void	free_split_result(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/*
 * Count elements in split result
 * 
 * Helper function to count how many strings are in the result array.
 * Useful for iteration or validation.
 */
int	split_count(char **split)
{
	int	count;

	if (!split)
		return (0);
	count = 0;
	while (split[count])
		count++;
	return (count);
}
