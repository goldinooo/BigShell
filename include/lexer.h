#ifndef TOKENIZE_H
# define TOKENIZE_H

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>


#define SQUOTE '\''
#define DQUOTE '"'

#define REDIR_IN '<'
#define REDIR_OUT '>'
#define PIPE '|'

typedef enum e_tktype
{
	TK_WORD,
	TK_PIPE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_APPEND_OUT,
	TK_HEREDOC
}	t_tktype;

typedef struct s_token
{
	char			*value;
	t_tktype		type;
	struct s_token	*next;
}	t_token;

bool		is_op(char ch);
bool		is_pipe(char ch);
bool		is_redir(char ch, int dir);
t_token		*create_token(char *value, t_tktype type);
void		add_token(t_token **tokens, t_token *new_token);
void		lexer(char *input, t_token **tokens);
void		free_tokens(t_token *tokens);
size_t		skip_spaces(char *input, size_t idx);
size_t		get_word_end(char *input, size_t start);

#endif