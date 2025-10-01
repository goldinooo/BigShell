#ifndef PARSER_H
#define PARSER_H


typedef struct s_redir 
{
	struct s_redir *next;
} t_redir;

typedef struct s_cmd
{
	char	**args;
	t_redir	*redir;
	struct s_cmd	*next;
}	t_cmd;

#endif