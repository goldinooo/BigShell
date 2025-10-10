/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_guard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 00:55:33 by retahri           #+#    #+#             */
/*   Updated: 2025/10/10 07:32:45 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp.h"
#include "lexer.h"
#include "lib.h"
#include "parsing.h"
#include <stdlib.h>

bool	multiple_args(char *value, bool space, bool squotes, bool dquotes)
{
	int	idx;

	idx = 0;
	while (value[idx])
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

char	**append_args(char **av, char *value, int *pos, int sub)
{
	int		idx;
	int		len;
	char	**new;
	char	**buf;

	idx = 0;
	buf = ft_split(value, ' ');
	len = args_len(av) + args_len(buf);
	new = (char **)malloc((len + 1) * sizeof(char *));
	while (idx < *pos)
	{
		new[idx] = ft_strdup(av[idx]);
		free(av[idx++]);
	}
	while (buf[sub])
		new[idx++] = ft_strdup(buf[sub++]);
	sub = *pos + 1;
	while (av[sub])
	{
		new[idx++] = ft_strdup(av[sub]);
		free(av[sub]);
		sub++;
	}
	*pos += (args_len(buf) - 1);
	return (new[idx] = NULL, free(value), free(av), clr_char_array(buf), new);
}
