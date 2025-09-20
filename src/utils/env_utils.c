#include "../../minishell.h"

t_env *new_env(void)
{
	t_env *node;

	node = malloc(sizeof(t_env));
	if(!node)
		return (NULL);
	node->next = NULL;
	return (node);
}

t_env	*next_env(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

void free_env(t_env **lst)
{
	t_env	*next;
	t_env	*current;

	if (!lst)
		return;
	current = *lst;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	*lst = NULL;
}
void env_add(t_env **lst, t_env *new_node)
{
	t_env *env;

	if (!lst || !new_node)
		return;
	if(!*lst)
	{
		*lst = new_node;
		return;
	}
	env = next_env(*lst);
	env->next = new_node;
}