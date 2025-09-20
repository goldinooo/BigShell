#include "../../minishell.h"


void fill_t_env(char **env, t_env **list)
{
	int idx;
	int eq;
	t_env *node;

	idx = 0;
	while (env[idx])
	{
		eq = croplen(env[idx], '=');
		if (!eq)
		{
			free_env(list);
			exit(0);
		}
		node->key = ft_substr(env[idx], 0, eq);
		node->value = ft_substr(env[idx], eq + 1, get_len(env[idx]) - eq);
		env_add(list, node);
		node = node->next;
		idx++;
	}
	
}


int init_env(char **env, t_env **list)
{
	*list = NULL;
	if(!list || env[0][0] == '\0')
	{
		*list = malloc(sizeof(t_env));
		if (!*list)
			return (-1);
		(*list)->key = NULL;
		(*list)->value = NULL;
	}
	else
		fill_t_env(env, list);
	return (0);
}