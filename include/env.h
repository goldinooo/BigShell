#ifndef ENV_H
#define ENV_H

#include "stdlib.h"


#define KEY_PATH "PATH"
#define BIN_PATH "/bin:/usr/bin"

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env *next;
} t_env;


//env.c

t_env *init_env(void);
t_env *parse_env(void);

//env_list_utils.c

t_env	*ft_lstnew_env(char *value, char *key);
t_env	*ft_lstlast_env(t_env *list);
void	ft_lst_back_env(t_env **lst, t_env *node);
void	ft_lst_clear_env(t_env **lst);


#endif