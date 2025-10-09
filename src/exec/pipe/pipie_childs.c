#include "minishell.h"

void ex_external_child(t_env **env, t_cmd *cmd)
{
	char **env_p;
	char *cmd_p;

	cmd_p = get_bin_path(cmd->args[0], *env);
	if(!cmd_p)
	{
		if (ft_strchr(cmd->args[0],'/') && access(cmd->args[0], F_OK) == 0)
			ft_putstr_fd("error", STDERR_FILENO);
		else
		{
			ft_putstr_fd("./minishell  ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[0], STDERR_FILENO);
			ft_putstr_fd("command not found", STDERR_FILENO);
		}
		exit(127);
	}
	env_p = env_to_arr(*env);
	execve(cmd_p, cmd->args, env_p);
	perror("execve");
	exit(127);
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
