#include "exp.h"
#include "lexer.h"
#include "minishell.h"
#include "parsing.h"
#include "utils.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stddef.h>
#include <stdio.h>
#include "exec.h"

void	process_line(char *line, t_shell *shell)
{
    t_token	*tokens;

    lexer(line, &tokens);
    parser(tokens, shell);
    free_tokens(tokens);
	expand(shell);
	execute(shell);
	clean_quotes(shell->cmd);
	if (!process_heredoc(shell))
	{
		//  TODO CLEANUP THE SHELL STRUCT
		return ;
	}
	/*
		? START TESTING
	*/
 	// if (shell->cmd)
    // {
    //     t_cmd *current = shell->cmd;
    //     int cmd_index = 0;

    //     printf("\n=== Command Structure ===\n");
    //     while (current)
    //     {
    //         printf("Command [%d]:\n", cmd_index);

    //         if (current->args)
    //         {
    //             printf("  Arguments: ");
    //             for (int i = 0; current->args[i]; i++)
    //             {
    //                 printf("'%s'", current->args[i]);
    //                 if (current->args[i + 1])
    //                     printf(", ");
    //             }
    //             printf("\n");
    //         }
    //         else
    //         {
    //             printf("  Arguments: (none)\n");
    //         }

    //         if (current->redir)
    //         {
    //             printf("  Redirections:\n");
    //             t_redir *redir_current = current->redir;
    //             int redir_index = 0;
    //             while (redir_current)
    //             {
    //                 printf("    [%d] Type: %zu, File: '%s'", redir_index, redir_current->type, redir_current->file);
    //                 if (redir_current->heredoc_fd != -1)
    //                     printf(", Heredoc FD: %d", redir_current->heredoc_fd);
    //                 printf(", Should expand: %s\n", redir_current->shouldexpand ? "true" : "false");
    //                 redir_current = redir_current->next;
    //                 redir_index++;
    //             }
    //         }
    //         else
    //         {
    //             printf("  Redirections: (none)\n");
    //         }

    //         printf("  ---\n");

    //         current = current->next;
    //         cmd_index++;
    //     }
    //     printf("=========================\n\n");
    // }
    // else
    // {
    //     printf("No commands parsed.\n");
    // }
	/*
		? END TESTING
	*/

    if (shell->cmd)
    {
        lst_clear_cmd(shell->cmd);
        shell->cmd = NULL;
    }
}

char	*generate_prompt(t_shell *shell)
{
	return (ft_strdup("minishell $> "));
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