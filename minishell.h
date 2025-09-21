#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
enum e_token_type
{
	SINGLE_QUOTE, // '
	DOUBLE_QUOTE, // " "
	INPUT_RED, // <
	OUTPUT_RED, // >
	APPEND_RED, // >>
	HEREDOC, // <<
	PIPE, // |
	WORD, // a word (command or argument)
};

typedef struct t_env
{
	char *key; //the name of the environment variable example: PATH  env
	char *value; //the value of the environment variable example: /usr/bin:/bin
	struct t_env *next; //pointer to the next node in the linked list
}               t_env;

typedef struct t_token
{
	char *value; //the actual string value of the token
	enum e_token_type type; //the type of token (e.g., command, argument, operator)
	struct t_token *next; //pointer to the next token in the linked list
}               t_token;

typedef struct t_redir
{
	int type;
	char *file;
	int fd;
}	t_redir;


typedef struct t_cmd
{
	char **av;
	t_redir *redir;
	int num_of_redir;
	int bi_type;
	struct t_cmd *next;
}	t_cmd;

//utils/env.c

int init_env(char **env, t_env **list);

// utils/str_man.c
size_t	 croplen(char *s, char to_cut);
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t 	get_len(char *s);

// utils/env_utils.c
void 	env_add(t_env **lst, t_env *new_node);
void 	free_env(t_env **lst);
t_env	*next_env(t_env *env);
t_env 	*new_env(void);


#endif