#ifndef UTILS_H
#define UTILS_H

typedef struct s_shell	t_shell;
typedef struct s_env	t_env;

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

/*
	./utils/env_to_arr.c
*/
char	**env_to_arr(t_env *env);

#endif