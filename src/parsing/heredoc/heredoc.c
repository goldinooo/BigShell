/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:18:47 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/11 00:12:53 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child_proc(t_shell *shell, t_redir *redir)
{
	ssize_t	fd;
	char	*line;

	init_heredoc_signals();
	fd = open(TMP_HD, O_CREAT | O_RDWR | O_TRUNC, 0644);
	redir->file = app_char(redir->file, '\n');
	if (!redir->file || fd == -1)
		exit(EXIT_FAILURE);
	line = NULL;
	while (true)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			(close(fd), exit(EXIT_FAILURE));
		}
		if (!ft_strcmp(line, redir->file))
			(free(line), close(fd), exit(EXIT_SUCCESS));
		if (redir->shouldexpand)
			line = expand_heredoc(shell, line);
		(ft_putstr_fd(line, fd), free(line));
	}
}

bool	exec_heredoc(t_shell *shell, t_redir *redir)
{
	pid_t	pid;
	int		status;

	ignore_main_sigint();
	pid = fork();
	if (pid == -1)
		return (false);
	else if (pid == 0)
		exec_child_proc(shell, redir);
	else
	{
		waitpid(pid, &status, 0);
		init_main_signals();
		redir->heredoc_fd = open(TMP_HD, O_RDONLY);
		unlink(TMP_HD);
		if (WEXITSTATUS(status) == SIG_KILLED)
			return (shell->exit_status = WEXITSTATUS(status), false);
		shell->exit_status = EXIT_SUCCESS;
	}
	return (true);
}

bool	process_heredoc(t_shell *shell)
{
	t_cmd	*curr_cmd;
	t_redir	*curr_redir;

	curr_cmd = shell->cmd;
	while (curr_cmd)
	{
		curr_redir = curr_cmd->redir;
		while (curr_redir)
		{
			if (curr_redir->type == TK_HEREDOC)
			{
				if (!exec_heredoc(shell, curr_redir))
					return (false);
			}
			curr_redir = curr_redir->next;
		}
		curr_cmd = curr_cmd->next;
	}
	return (true);
}
