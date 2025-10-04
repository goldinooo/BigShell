#include "exec.h"
#include "exp.h"
#include "lib.h"
#include "minishell.h"
#include "parsing.h"
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>



int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}
void	exec_builtin(t_shell *shell, char **args)
{
	int		save_stdout;
	int		save_stdin;

	if (!setup_with_backup(shell->cmd, &save_stdout, &save_stdin))
		return ;
	if (!ft_strcmp(args[0], "echo"))
		ex_echo(shell, args);
	else if (!ft_strcmp(args[0], "cd"))
		ex_cd(shell, args);
	else if (!ft_strcmp(args[0], "pwd"))
		ex_pwd(shell);
	else if (!ft_strcmp(args[0], "env"))
		ex_env(shell);
	else if (!ft_strcmp(args[0], "export"))
		ex_export(shell, args);
	else if (!ft_strcmp(args[0], "unset"))
		ex_unset(shell, args);
	else if (!ft_strcmp(args[0], "exit"))
		ex_exit(shell, args);
	dup2(save_stdout, STDOUT_FILENO);
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	close(save_stdout);
}

void	exec_in_child(t_shell *shell, t_cmd *cmd, char *bin_path)
{
	char	**envp;
	pid_t	pid;
	int		status;

	envp = env_to_arr(shell->env);
	if (!envp)
		return ; //TODO Handle the malloc errors.
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		reset_and_catch_sig(shell, status, true);
	}
	else
	{
		reset_and_catch_sig(shell, status, true);
		if (!init_redirection(cmd))
			exit(1);
		execve(bin_path, cmd->args, envp);
		(perror("execve"), exit(1));
	}
}

void	exec_bin(t_shell *shell, t_cmd *cmd)
{
	char	*bin_path;
	bool	has_slash;

	bin_path = get_bin_path(cmd->args[0], shell->env);
	if (!bin_path)
	{
		has_slash = (ft_strchr(cmd->args[0], '/') != NULL);
		if (has_slash && !access(cmd->args[0], F_OK))
		{
			shell->exit_status = EACCES;
			perror(cmd->args[0]);
		}
		else
		{
			shell->exit_status = ENOENT;
			if (has_slash)
				perror(cmd->args[0]);
			else
				return ; // TODO Print the command not found error
		}
	}
	exec_in_child(shell, cmd, bin_path);
}

void execute(t_shell *shell)
{
	t_cmd *tmp;
	int prev_fd;

	if (!shell || !shell->cmd)
		return ;
	tmp = shell->cmd;
	prev_fd = -1;
	if (tmp->next)
	{
		ex_pipe(shell, prev_fd, -1);
		return;
	}
	if(!tmp->args || !tmp->args[0] || !tmp->args[0][0])
		return;
	if (is_builtin(tmp->args[0]))
		exec_builtin(shell, tmp->args);
	else
		exec_bin(shell, tmp);
}