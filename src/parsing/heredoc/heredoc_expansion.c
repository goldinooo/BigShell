/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:28:23 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/02 20:20:27 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exp.h"
#include "utils.h"
#include <stdbool.h>

bool	should_heredoc_expand(t_redir *redir)
{
	if (ft_strchr(redir->file, '"')	|| ft_strchr(redir->file, '\''))
		return (redir->shouldexpand = false, false);
	return (true);
}

char	*expand_heredoc(t_shell *shell, char *line)
{
	size_t	idx;
	t_exp	exp;

	init_exp(&exp);
	idx = 0;
	while (line[idx])
	{
		if (valid_exp(line[idx], line[idx + 1], false))
			expander_magic(&exp, line, &idx, shell);
		else
			exp.output = app_char(exp.output, line[idx]);
		idx++;
	}
	free(line);
	return (exp.output);
}
