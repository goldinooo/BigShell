/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retahri <retahri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 01:05:08 by retahri           #+#    #+#             */
/*   Updated: 2025/10/10 01:07:57 by retahri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "lexer.h"

# define EXIT_SIG 30
# define TMP_HD "/tmp/.doctorishere.tmp"

typedef struct s_shell	t_shell;

typedef struct s_redir
{
	char				*file;
	int					heredoc_fd;
	bool				shouldexpand;
	size_t				type;
	struct s_redir		*next;
}						t_redir;

typedef struct s_cmd
{
	char				**args;
	t_redir				*redir;
	struct s_cmd		*next;
}						t_cmd;

void					parser(t_token *tokens, t_shell *shell);

bool					is_valid_syntax(t_token *tokens);

/*
	Cmds & Redirs lists funtions
*/
t_cmd					*lst_new_cmd(char *args[]);
t_cmd					*lst_last_cmd(t_cmd *cmds);
t_cmd					*lst_append_cmd(t_cmd *cmds, t_cmd *node);
void					lst_clear_cmd(t_cmd *cmds);

t_redir					*lst_new_redir(size_t type, char *file);
t_redir					*lst_last_redir(t_redir *redirs);
t_redir					*lst_append_redirs(t_redir *redirs, t_redir *node);
void					lst_clear_redirs(t_redir *redirs);

/*
	Cleaning functions
*/
void					clr_char_array(char **array);

/*
	Cmds && redirs filling
*/
char					**fill_cmds(t_token *tokens, size_t cmds);

/*
	Fill functions
*/
t_redir					*fill_redirs(t_token *tokens, size_t redirs);

/*
	Parser utils
*/
bool					is_valid_pipe(t_token *prev, t_token *curr);
bool					is_valid_redir(t_token *curr);

/*
	heredoc
*/

bool					process_heredoc(t_shell *shell);
void					ignore_main_sigint(void);
bool					should_heredoc_expand(t_redir *redir);
char					*expand_heredoc(t_shell *shell, char *line);
void					init_heredoc_signals(void);

#endif