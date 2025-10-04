#include "exp.h"
#include "lexer.h"
#include "minishell.h"
#include "parsing.h"
#include "lib.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "exec.h"

void	process_line(char *line, t_shell *shell)
{
    t_token	*tokens;

    lexer(line, &tokens);
    parser(tokens, shell);
    free_tokens(tokens);
	expand(shell);
	clean_quotes(shell->cmd);
	if (!process_heredoc(shell))
	{
		//  TODO CLEANUP THE SHELL STRUCT
		return ;
	}
	execute(shell);
    if (shell->cmd)
    {
        lst_clear_cmd(shell->cmd);
        shell->cmd = NULL;
    }
}

char	*generate_prompt(t_shell *shell)
{
	return (ft_strdup("\nminishell $> "));
}

void	interactive_mode(t_shell *shell)
{
    char	*input;
	char	*prompt;

	init_main_signals();
	while (true)
	{
		prompt = generate_prompt(shell);
		input = readline(prompt);
		free(prompt);
		if (!input)
			break ;
		else
		{
			add_history(input);
			process_line(input, shell);
		}
	}
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
    t_shell	shell;

    shell.env = init_env();
    shell.cmd = NULL;
    shell.exit_status = 0;

    // Check for test mode
    if (isatty(STDIN_FILENO))
        interactive_mode(&shell);
    else
        script_mode(STDIN_FILENO, &shell);
    return (0);
}