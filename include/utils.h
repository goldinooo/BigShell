#ifndef UTILS_H
#define UTILS_H

typedef struct s_shell	t_shell;

/*
	print_errors.c
*/
void print_error_fd(char *str, t_shell *shell);
void print_perror(char *str, t_shell *shell);
void exit_with_status(t_shell *shell, int status);
/*
	count_args.c
*/
int args_len(char **args);

#endif