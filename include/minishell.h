/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retahri <retahri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 00:52:57 by retahri           #+#    #+#             */
/*   Updated: 2025/10/10 01:03:55 by retahri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "env.h"
# include "exec.h"
# include "lib.h"
# include "parsing.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/stat.h>
# define EXIT_SIGNAL 128
# define SIG_KILLED 130
# define EXIT_SYNTAX 2
# define EXIT_PERM 126
# define EXIT_CMD_NF 127
# define SHELL_NAME "Minishell"
# define PREFIX "Minishell: cd: "

extern char				**environ;

typedef struct s_env	t_env;
typedef struct s_shell
{
	t_env				*env;
	t_cmd				*cmd;
	int					exit_status;
}						t_shell;

void	init_main_signals(void);
void	ignore_main_sigint(void);
bool	clean_quotes(t_cmd *cmd);
int		is_valid_id(char *str);
void	print_any(char **cmd);
void	ll(char **args, t_shell *shell);
void	bprint_err(char **cmd, char *msg);
char	**env_to_arr(t_env *env);
int		args_len(char **args);
void	print_error_fd(char *str, t_shell *shell);
void	exit_with_status(t_shell *shell, int status);
void	clean_shell(t_shell *shell);

#endif