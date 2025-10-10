/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 03:34:52 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/10 00:56:54 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include <stdbool.h>
#include <stddef.h>

static int	init_redir_fd(void)
{
	int	fd;

	fd = dup(STDOUT_FILENO);
	if (fd == -1)
		return (-1);
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
		return (close(fd), -1);
	return (fd);
}

static bool	is_quotes_unclosed(char *token)
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
		bprint_err(NULL, "you have some unclosed buisness.");
		return (false);
	}
	return (true);
}

static int	restore_redir_fd(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), -1);
	close(fd);
	return (fd);
}

bool	is_valid_syntax(t_token *tokens)
{
	t_token	*curr;
	t_token	*prev;
	int		fd;

	fd = init_redir_fd();
	if (fd == -1)
		return (false);
	prev = tokens;
	curr = tokens;
	while (curr)
	{
		if (!is_quotes_unclosed(curr->value))
			return (false);
		else if (!is_valid_pipe(prev, curr))
			return (false);
		else if (!is_valid_redir(curr))
			return (false);
		prev = curr;
		curr = curr->next;
	}
	fd = restore_redir_fd(fd);
	if (fd == -1)
		return (false);
	return (true);
}
