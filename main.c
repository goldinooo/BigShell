/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 00:56:38 by retahri           #+#    #+#             */
/*   Updated: 2025/10/10 04:04:55 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env.h"
#include "exp.h"
#include "lexer.h"
#include "lib.h"
#include "minishell.h"
#include "parsing.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

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
	char	*username;
	char 	cwd[1024];
	char	*prompt;
	char	*tmp;

	username = value_from_env(ft_strdup("USER"), shell->env);
	if (!username)
		return (NULL);
	getcwd(cwd, sizeof(cwd));
	prompt = ft_strjoin(username, "\e[1;35m@\e[1;32m");
	tmp = prompt;
	prompt = ft_strjoin(prompt, SHELL_NAME);
	free(tmp);
	tmp = prompt;
	prompt = ft_strjoin(prompt, "\e[1;35m:\e[1;32m");
	free(tmp);
	tmp = prompt;
	prompt = ft_strjoin(prompt, cwd);
	free(tmp);
	tmp = prompt;
	prompt = ft_strjoin("\e[1;32m", prompt);
	free(tmp);
	tmp = prompt;
	prompt = ft_strjoin(prompt, "\n︻芫═─── \e[1;35m$>\e[0m ");
	return (free(tmp), prompt);
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

int main(void)
{
	t_shell	shell;

	shell.env = init_env();
	shell.cmd = NULL;
	shell.exit_status = 0;
	if (isatty(STDIN_FILENO))
		interactive_mode(&shell);
	else
		script_mode(STDIN_FILENO, &shell);
	return (shell.exit_status);
}
