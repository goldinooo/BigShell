/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 21:31:52 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/04 23:54:01 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexer.h"
#include "parsing.h"
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>

bool	redir_in(t_redir *redir)
{
	int	fd;

	if (redir->type == TK_REDIR_IN)
	{
		fd = open(redir->file, O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				printf("Permission denied!");
			if (errno == ENOENT)
				printf("No such file or directory!");
			return (false);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
			return (close(fd), false);
		close(fd);
	}
	else
	{
		fd = dup2(redir->heredoc_fd, STDIN_FILENO);
		if (fd == -1)
			return (false);
		close(redir->heredoc_fd);
	}
	return (true);
}

bool	redir_out(t_redir *redir)
{
	int	fd;

	if (redir->type == TK_REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND);
	if (fd == -1)
		return (perror(redir->file), false);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror(redir->file), close(fd), false);
	close(fd);
	return (true);
}

bool	init_redirection(t_cmd *cmd)
{
	t_redir	*curr;

	if (!cmd || !cmd->redir)
		return (true);
	curr = cmd->redir;
	while (curr)
	{
		if (is_faulty_redir(curr))
			return (false);
		if (curr->type == TK_REDIR_IN || curr->type == TK_HEREDOC)
		{
			if (!redir_in(curr))
				return (false);
		}
		else if (curr->type == TK_REDIR_OUT || curr->type == TK_APPEND_OUT)
		{
			if (!redir_out(curr))
				return (false);
		}
		curr = curr->next;
	}
	return (true);
}
