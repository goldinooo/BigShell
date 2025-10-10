/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 00:52:50 by retahri           #+#    #+#             */
/*   Updated: 2025/10/10 07:51:01 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define SQUOTE 39
# define DQUOTE 34

# define REDIR_IN 60
# define REDIR_OUT 62
# define PIPE 124

typedef enum e_tktype
{
	TK_WORD = 0,
	TK_PIPE = 1,
	TK_REDIR_IN = 2,
	TK_REDIR_OUT = 3,
	TK_APPEND_OUT = 4,
	TK_HEREDOC = 5,
}					t_tktype;

typedef struct s_token
{
	char			*value;
	t_tktype		type;
	struct s_token	*next;
}					t_token;

bool				is_op(char ch);
bool				is_pipe(char ch);
bool				is_redir(char ch, int dir);
t_token				*create_token(char *value, t_tktype type);
void				add_token(t_token **tokens, t_token *new_token);
void				lexer(char *input, t_token **tokens);
void				free_tokens(t_token *tokens);
size_t				skip_spaces(char *input, size_t idx);
size_t				get_word_end(char *input, size_t start);

#endif