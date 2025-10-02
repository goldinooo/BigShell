/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 03:34:52 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/01 03:57:54 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include <stdbool.h>
#include <stddef.h>

bool	init_redir_fd(int *fd)
{
	*fd = dup(STDOUT_FILENO);
	if (*fd == -1)
		return (false);
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
		return (close(*fd), false);
	return (true);
}

bool	is_quotes_unclosed(char *token)
{
	char	quote;

	quote = 0;
	while (*token)
	{
		if ((*token == SQUOTE || *token == DQUOTE) && !quote)
			quote = *token;
		else if (*token == quote)
			quote = 0;
		token++;
	}
	if (quote)
	{
		// TODO Print the quote error
		return (false);
	}
	return (true);
}

bool	is_pipe_valid(t_token *prev, t_token *curr)
{
	if (curr->type == TK_PIPE)
	{
		if (prev->type != TK_WORD)
			// TODO Print the invalid pipe error
			return (false);
		if (!curr->next)
			// TODO Print the invalid pipe error
			return (false);
	}
	return (true);
}

bool	is_valid_redir(t_token *curr)
{
	unsigned int	type;

	type = curr->type;
	if (type == TK_REDIR_IN || type == TK_REDIR_OUT
		|| type == TK_APPEND_OUT || type == TK_HEREDOC)
	{
		if (!curr->next)
		{
			// TODO Print the invalid redir error
			return (false);
		}
		else if (curr->next->type != TK_WORD)
		{
			// TODO Prin the invalid token error
			return (false);
		}
	}
	return (true);
}

bool	restore_redir_fd(int *fd)
{
	if (dup2(*fd, STDOUT_FILENO) == -1)
		return (close(*fd), false);
	close(*fd);
	return (true);
}


bool	is_valid_syntax(t_token *tokens)
{
	t_token	*curr;
	t_token	*prev;
	int		fd;

	if (!init_redir_fd(&fd))
		return (false);
	prev = tokens;
	curr = tokens;
	while (curr)
	{
		if (!is_quotes_unclosed(curr->value))
			return (false);
		else if (!is_pipe_valid(prev, curr))
			return (false);
		else if (!is_valid_redir(curr))
			return (false);
		prev = curr;
		curr = curr->next;
	}
	if (!restore_redir_fd(&fd))
		return (false);
	return (true);
}
