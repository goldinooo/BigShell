#include "env.h"
#include "exec.h"
#include "exp.h"
#include "lexer.h"
#include "lib.h"
#include "minishell.h"
#include "parsing.h"
#include "utils.h"
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


void ex_external_child(t_env **env, t_cmd *cmd)
{
	char **env_p;
	char *cmd_p;

	cmd_p = get_bin_path(cmd->args[0], *env);
	if(!cmd_p)
	{
		if (ft_strchr(cmd->args[0],'/') && access(cmd->args[0], F_OK) == 0)
			ft_putstr_fd("errrooorr  a ba dyali", STDERR_FILENO);
		else
		{
			ft_putstr_fd("./minishell  ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[0], STDERR_FILENO);
			ft_putstr_fd("command not found a khawa dyali", STDERR_FILENO);
		}
		exit(127);
	}
	env_p = env_to_arr(*env);
	execve(cmd_p, cmd->args, env_p);
	perror("execve");
	exit(127);
}


bool setup_with_backup(t_cmd *cmd, int *save_stdout, int *save_stdin)
{
	*save_stdout = dup(STDOUT_FILENO);
	*save_stdin = dup(STDIN_FILENO);
	if(!init_redirection(cmd))
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

bool cmd_redir_output(t_cmd *cmd)
{
	t_redir *red;

	if (!cmd || !cmd->redir)
		return (false);
	red = cmd->redir;
	while(red)
	{
		if(red->type == TK_REDIR_OUT || red->type == TK_APPEND_OUT)
			return (true);
		red = red->next;
	}
	return (false);
}


void setup_io(t_cmd *cmd, int prev_fd, int pipedes[2])
{
	if(prev_fd != -1)
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
	else if(cmd->next)
	{
		close(pipedes[0]);
		close(pipedes[1]);
	}
}


void ex_child(t_shell *shell, t_cmd *cmd, int prev_fd, int pipedes[2])
{
	signal(SIGINT,  SIG_DFL);
	signal(SIGQUIT,  SIG_DFL);
	setup_io(cmd, prev_fd, pipedes);
	if(!init_redirection(cmd))
		exit(EXIT_FAILURE);
	if (is_builtin(cmd->args[0]))
		exec_builtin(shell, cmd->args);
	else
		ex_external_child(&shell->env, cmd);
	exit(EXIT_SUCCESS);
}
static void parent_fds(int prev_fd, int pipedes[2], t_cmd *cmd)
{
	if(prev_fd != -1)
		close(prev_fd);
	if(cmd->next)
		close(pipedes[1]);
}
void	ex_pipe(t_shell *shell, int prev_fd, pid_t pid)
{
	t_cmd *cmd;
	int pipedes[2];
	int status;

	cmd = shell->cmd;
	while(cmd)
	{
		if (cmd->next)
			pipe(pipedes);
		pid = fork();
		if(pid == 0)
			ex_child(shell, cmd, prev_fd, pipedes);
		parent_fds(prev_fd, pipedes, cmd);
		if (cmd->next)
			prev_fd = pipedes[0];
		cmd = cmd->next;
	}
	waitpid(pid, &status, 0);
	while(wait(NULL) > 0);
	reset_and_catch_sig(shell, status, false);
}
