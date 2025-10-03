#include "exp.h"
#include "minishell.h"
#include "parsing.h"



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

	// if (!setup_with_backup(shell->cmd, &save_stdout, &save_stdin))
	// 	return ;
	if (!ft_strcmp(args[0], "echo"))
		ex_echo(shell, args);
	else if (!ft_strcmp(args[0], "cd"))
		ex_cd(shell, args);
	else if (!ft_strcmp(args[0], "pwd"))
		ex_pwd(shell);
	else if (!ft_strcmp(args[0], "env"))
		ex_env(shell);
	// dup2(save_stdout, STDOUT_FILENO);
	// dup2(save_stdin, STDIN_FILENO);
	// close(save_stdin);
	// close(save_stdout);
}

void execute(t_shell *shell)
{
	t_cmd *tmp;
	int prev_fd;

	if (!shell || !shell->cmd)
		return ;
	tmp = shell->cmd;
	prev_fd = -1;
	if (!tmp->args || !tmp->args[0] || !tmp->args[0][0])
		return ;
	if (is_builtin(tmp->args[0]))
		exec_builtin(shell, tmp->args);
}