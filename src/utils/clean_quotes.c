/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 04:57:10 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/03 21:02:21 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp.h"
#include "lexer.h"
#include "parsing.h"
#include "lib.h"
#include <stdbool.h>
#include <stddef.h>

static char	*clean_outer_quotes(char *arg)
{
	size_t	idx;
	bool	squote;
	bool	dquote;
	char	*cleaned;

	(idx = 0, squote = false, dquote = false);
	cleaned = ft_strdup("");
	if (!cleaned)
		return (NULL);
	while (arg[idx])
	{
		if (arg[idx] == SQUOTE && !dquote)
			squote = !squote;
		else if (arg[idx] == DQUOTE && !squote)
			dquote = !dquote;
		else
		{
			cleaned = app_char(cleaned, arg[idx]);
			if (!cleaned)
				return (NULL);
		}
		idx++;
	}
	return (cleaned);
}

static bool	clean_redir_quotes(t_redir *redir)
{
	t_redir	*curr;
	char	*tmp;

	curr = redir;
	while (curr)
	{
		if (curr->file[0] == SQUOTE || curr->file[0] == DQUOTE)
			curr->shouldexpand = false;
		tmp = curr->file;
		curr->file = clean_outer_quotes(curr->file);
		if (!curr->file)
			return (false);
		free(tmp);
		curr = curr->next;
	}
	return (true);
}

bool	clean_quotes(t_cmd *cmd)
{
	size_t	idx;
	t_cmd	*curr;
	char	*tmp;

	curr = cmd;
	while (curr)
	{
		idx = 0;
		while (curr->args[idx])
		{
			tmp = curr->args[idx];
			curr->args[idx] = clean_outer_quotes(curr->args[idx]);
			if (!curr->args[idx])
				return (false);
			free(tmp);
			idx++;
		}
		clean_redir_quotes(curr->redir);
		curr = curr->next;
	}
	return (true);
}
