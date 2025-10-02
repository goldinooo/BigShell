#include "lexer.h"
#include "minishell.h"
#include "parsing.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>

void	process_line(char *line, t_shell *shell)
{
	t_token	*tokens;

	lexer(line, &tokens);  // TODO Fix the malloc errors, and properly handle in the lexer functions
	// TODO: parser
	parser(tokens, shell); // TODO Properly handle the parser errors
	//? For testing parser
	// free_tokens(tokens);
	// t_cmd	*cmd;
	// t_redir	*redir;
	// size_t	idx;
	// size_t	sub;

	// cmd = shell->cmd;
	// sub = 0;
	// while (cmd)
	// {
	// 	idx = 0;
	// 	while (cmd->args[idx])
	// 	{
	// 		printf("\"%s\" ", cmd->args[idx]);
	// 		idx++;
	// 	}
	// 	printf("\n");
	// 	redir = cmd->redir;
	// 	while (redir)
	// 	{
	// 		printf("file: \"%s\"\n", redir->file);
	// 		printf("redir type: \"%zu\"\n", redir->type);
	// 		printf("should expand: \"%d\"\n", redir->shouldexpand);

	// 		redir = redir->next;
	// 	}
	// 	sub++;
	// 	cmd = cmd->next;
	// }
	// printf("len: %zu\n", sub);
	// lst_clear_cmd(shell->cmd);
	exit(0);
}

void	interactive_mode(/*Takes the shell struct*/)
{

}

void	script_mode(int fd, t_shell *shell)
{
	char	*line;

	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		process_line(line, shell);
		free(line);
	}
}

int main(int ac, char **av)
{
	// init & process the envs
	t_shell	shell;

	shell.env = init_env();
	shell.cmd = NULL;
	if (isatty(STDIN_FILENO))
		interactive_mode(/*Takes the shell struct*/);
	else
		script_mode(STDIN_FILENO, &shell);
	return (0);
}

