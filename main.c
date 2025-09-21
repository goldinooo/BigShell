#include "minishell.h"

int main(int ac, char **av/*, char **env*/)
{
	// t_env	*list;
	t_token	*tokens;
	t_cmd 	*cmd;
	char	*args;

	tokens = NULL;
	cmd = NULL;
	// if (ac != 1 || init_env(env, &list) < 0)
	// 	return (0);
	(void)ac;
	(void)av;
	while (1337)
	{
		args = readline("bigshell -->  ");
		if (!args)
			return 0;
		add_history(args);
		free(args);
	}
	return 0;
}
