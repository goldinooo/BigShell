#ifndef PARSER_H
#define PARSER_H

typedef struct s_cmd
{
	char **args;
	struct s_cmd *next;
}	t_cmd;

#endif