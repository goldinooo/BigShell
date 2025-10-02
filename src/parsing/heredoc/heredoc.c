// #include "heredoc.h"
// #include "minishell.h"
// #include "parsing.h"
// #include "utils.h"
// #include <fcntl.h>
// #include <stdlib.h>
// #include <unistd.h>


// void	child_process(t_redir *red, t_shell *shell, char *line)
// {
// 	int		fd;

// 	setup_heredoc_signals();
// 	fd = open(TMP_HD, O_CREAT | O_RDWR | O_TRUNC, 0644); // !
// 	red->file = ft_strjoin(red->file, "\n");
// 	while(1337)
// 	{
// 		ft_putstr_fd("-> ", STDOUT_FILENO);
// 		line = get_next_line(STDIN_FILENO);
// 		if (!line)
// 		{
// 			ft_putstr_fd("\n", STDOUT_FILENO);
// 			break;
// 		}
// 		line = ft_strjoin(line, "\n");
// 		if (!ft_strcmp(line, red->file))
// 		{
// 			free(line);
// 			break;
// 		}
// 		// if(red->shouldexpand)
// 		// 	line = expandhd;
// 	}
// 	(close(fd), exit(EXIT_SUCCESS));
// }

// int run_heredoc(t_redir *red, t_shell *shell)
// {
// 	int status;
// 	pid_t pid;

// 	ignore_sigint();
// 	pid = fork();
// 	if(pid == -1)
// 		return (EXIT_FAILURE);
// 	else if (pid == 0)
// 		child_process(red, shell,NULL);
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 		setup_heredoc_signals();
// 		red->heredoc_fd = open(TMP_HD, O_RDONLY);
// 		unlink(TMP_HD);
// 	}


// }


// // int heredoc(t_shell *shell)
// // {
// // 	t_redir *red;
// // 	t_cmd *cmd;

// // 	cmd = shell->cmd;
// // 	while (cmd)
// // 	{
// // 		red = cmd->redir;
// // 		while (red)
// // 		{
// // 			if (red->type == TK_HEREDOC && )
// // 		}
// // 	}
// // }