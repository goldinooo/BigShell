/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retahri <retahri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 00:55:42 by retahri           #+#    #+#             */
/*   Updated: 2025/10/10 00:55:43 by retahri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp.h"
#include "lib.h"
#include <stdbool.h>
#include <stdlib.h>

bool	should_expand(bool squote)
{
	return (!squote);
}

void	init_exp(t_exp *exp)
{
	exp->output = ft_strdup("");
	exp->var = NULL;
	exp->is_squote = false;
	exp->is_dquote = false;
	exp->start_pos = 0;
}

char	*app_char(char *s, char c)
{
	char	*str;
	int		idx;

	idx = -1;
	if (!s)
		return (NULL);
	str = malloc((ft_strlen(s) + 3) * sizeof(char));
	if (!str)
		return (NULL);
	while (s[++idx])
		str[idx] = s[idx];
	str[idx++] = c;
	str[idx] = '\0';
	free(s);
	return (str);
}

void	handle_quotes(t_exp *exp, char c, bool squote)
{
	if (squote)
		exp->is_squote = !exp->is_squote;
	else
		exp->is_dquote = !exp->is_dquote;
	exp->output = app_char(exp->output, c);
}

bool	valid_expand(char c, char next, bool squote)
{
	if (c == '$')
	{
		if (should_expand(squote) && (ft_isalpha(next) || next == '_'
				|| next == '?'))
			return (true);
	}
	return (false);
}