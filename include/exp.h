/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 01:12:15 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/03 05:50:11 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXP_H
# define EXP_H

#include "lexer.h"
#include "utils.h"
#include "env.h"
#include <stdbool.h>

typedef struct s_shell	t_shell;
typedef struct s_redir	t_redir;

typedef struct s_exp
{
	char	*output;
	char	*var;
	int		start_pos;
	bool	is_squote;
	bool	is_dquote;
}	t_exp;

// expansion_utils

void	init_exp(t_exp *exp);
void	handle_quotes(t_exp *exp, char c, bool squote);
char	*app_char(char *s, char c);
bool	should_expand(bool squote);
bool	valid_expand(char c, char next, bool squote);

// expand_guard

bool	multiple_args(char *value, bool space, bool squotes, bool dquotes);
int		args_len(char **args);
char	**append_args(char **args, char *value, int *pos, int sub);

// expand.c

int 	expander_magic(t_exp *exp, char *value, int i, t_shell *shell);
int		skip_and_join(t_exp *exp, char *value, int i);
char 	*expand_var(t_shell *shell, char *value);
void	exp_redir(t_redir *red, t_shell *shell);
void	expand(t_shell *shell);



#endif