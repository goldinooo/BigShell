/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retahri <retahri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 00:55:07 by retahri           #+#    #+#             */
/*   Updated: 2025/10/10 02:12:11 by retahri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "exp.h"
#include "lexer.h"
#include "lib.h"
#include "minishell.h"
#include "parsing.h"
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

bool	setup_with_backup(t_cmd *cmd, int *save_stdout, int *save_stdin)
{
	*save_stdout = dup(STDOUT_FILENO);
	*save_stdin = dup(STDIN_FILENO);
	if (!init_redirection(cmd))
	{
		close(*save_stdin);
		close(*save_stdout);
		return (false);
	}
	return (true);
}

void	reset_and_catch_sig(t_shell *shell, int status, bool toggle)
{
	if (toggle)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exit_status = WTERMSIG(status) + EXIT_SIGNAL;
	}
}

void	setup_io(t_cmd *cmd, int prev_fd, int pipedes[2])
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next && !cmd_redir_output(cmd))
	{
		dup2(pipedes[1], STDOUT_FILENO);
		close(pipedes[0]);
		close(pipedes[1]);
	}
	else if (cmd->next)
	{
		close(pipedes[0]);
		close(pipedes[1]);
	}
}

static void	parent_fds(int prev_fd, int pipedes[2], t_cmd *cmd)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->next)
		close(pipedes[1]);
}

void	ex_pipe(t_shell *shell, int prev_fd, pid_t pid)
{
	t_cmd	*cmd;
	int		pipedes[2];
	int		status;

	cmd = shell->cmd;
	while (cmd)
	{
		if (cmd->next)
			pipe(pipedes);
		pid = fork();
		if (pid == 0)
			ex_child(shell, cmd, prev_fd, pipedes);
		parent_fds(prev_fd, pipedes, cmd);
		if (cmd->next)
			prev_fd = pipedes[0];
		cmd = cmd->next;
	}
	waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		;
	reset_and_catch_sig(shell, status, false);
}
