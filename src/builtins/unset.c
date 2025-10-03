#include "env.h"
#include "exp.h"
#include "minishell.h"
#include "utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


static void clean_env_key(char *key, t_env **env)
{
	t_env *curr;
	t_env *prev;

	if (!env || !*env)
		return;
	curr = *env;
	prev = NULL;
	while(curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			if(curr->value)
				free(curr->value);
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

static void unset_var(char *arg, t_shell *shell)
{
	if(is_valid_id(arg))
	{
		shell->exit_status = EXIT_SUCCESS;
		clean_env_key(arg, &shell->env);
	}
	else
	{
		shell->exit_status = EXIT_FAILURE;
		perror("had error ghalat");
	}
}

void ft_unset(t_shell *shell, char **args)
{
	int idx;

	if (!args || !args[1] || !shell || !shell->env)
		return;
	idx = 1;
	while(args[idx])
	{
		unset_var(args[idx], shell);
		idx++;
	}
}