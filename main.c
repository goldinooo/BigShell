#include "exp.h"
#include "lexer.h"
#include "minishell.h"
#include "parsing.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>


void	process_line(char *line, t_shell *shell)
{
    t_token	*tokens;

    lexer(line, &tokens);
    parser(tokens, shell);
	expand(shell);
    free_tokens(tokens);
    if (shell->cmd)
    {
        lst_clear_cmd(shell->cmd);
        shell->cmd = NULL;
    }
}

void	interactive_mode(/*Takes the shell struct*/)
{
    // Your interactive mode implementation
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
        interactive_mode(/*Takes the shell struct*/);
    else
        script_mode(STDIN_FILENO, &shell);
    return (0);
}