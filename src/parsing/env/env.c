/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 00:55:28 by retahri           #+#    #+#             */
/*   Updated: 2025/10/10 07:25:30 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "lib.h"
#include "minishell.h"

t_env	*init_env(void)
{
	t_env	*env;

	env = NULL;
	env = parse_env();
	if (!env)
	{
		env = malloc(sizeof(t_env));
		if (!env)
			return (NULL);
		env->key = ft_strdup(KEY_PATH);
		env->value = ft_strdup(BIN_PATH);
		env->next = NULL;
	}
	return (env);
}

t_env	*parse_env(void)
{
	int		idx;
	char	*eq;
	t_env	*env_list;
	t_env	*node;

	idx = 0;
	env_list = NULL;
	while (environ[idx])
	{
		eq = ft_strchr(environ[idx], '=');
		if (eq)
		{
			node = ft_lstnew_env(ft_strdup(eq + 1),
					ft_substr(environ[idx], 0, eq
						- environ[idx]));
			if (!node)
			{
				ft_lst_clear_env(&env_list);
				return (NULL);
			}
			ft_lst_back_env(&env_list, node);
		}
		idx++;
	}
	return (env_list);
}

char	*value_from_env(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
		{
			free(key);
			return (env->value);
		}
		env = env->next;
	}
	free(key);
	return (NULL);
}
