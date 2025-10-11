/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 02:08:55 by retahri           #+#    #+#             */
/*   Updated: 2025/10/11 23:00:24 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}

void	exec_builtin(t_shell *shell, char **args)
{
	int	save_stdout;
	int	save_stdin;

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

	if (!bin_path)
		return ;
	envp = env_to_arr(shell->env);
	if (!envp)
		return ;
	status = 0;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		clr_char_array(envp);
		return ;
	}
	else if (pid > 0)
	{
		clr_char_array(envp);
		waitpid(pid, &status, 0);
		reset_and_catch_sig(shell, status, false);
	}
	else
		child_proc(shell, cmd, bin_path);
}

void	exec_bin(t_shell *shell, t_cmd *cmd)
{
	struct stat	st;
	char		*bin_path;

	bin_path = get_bin_path(cmd->args[0], shell->env);
	if (!bin_path)
	{
		shell->exit_status = EXIT_PERM;
		if (stat(cmd->args[0], &st) == -1)
		{
			if (ft_strchr(cmd->args[0], '/'))
				bprint_err((char *[]){cmd->args[0], NULL}, "is a directory");
			else
			{
				shell->exit_status = EXIT_CMD_NF;
				bprint_err((char *[]){cmd->args[0], NULL},
					"command not found");
			}
		}
		else if (S_ISDIR(st.st_mode))
			bprint_err((char *[]){cmd->args[0], NULL}, "is a directory");
		else if (access(cmd->args[0], X_OK) == -1)
			bprint_err((char *[]){cmd->args[0], NULL}, "Permission denied");
		return ;
	}
	(exec_in_child(shell, cmd, bin_path), free(bin_path));
}

void	execute(t_shell *shell)
{
	t_cmd	*tmp;
	int		prev_fd;

	if (!shell || !shell->cmd)
		return ;
	tmp = shell->cmd;
	prev_fd = -1;
	if (tmp->next)
	{
		ex_pipe(shell, prev_fd, -1);
		return ;
	}
	if (!tmp->args || !tmp->args[0])
		return ;
	if (is_builtin(tmp->args[0]))
		exec_builtin(shell, tmp->args);
	else
		exec_bin(shell, tmp);
}
