/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 22:38:08 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/04 22:49:50 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "lib.h"
#include <stddef.h>

static size_t	env_len(t_env *env)
{
	t_env	*curr;
	size_t	idx;

	idx = 0;
	curr = env;
	while (curr)
	{
		idx++;
		curr = curr->next;
	}
	return (idx);
}

char	**env_to_arr(t_env *env)
{
	t_env	*curr;
	char	**envp;
	char	*tmp;
	size_t	idx;

	if (!env)
		return (NULL);
	envp = malloc((env_len(env) + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	idx = 0;
	curr = env;
	while (curr)
	{
		if (!curr->value)
		{
			tmp = ft_strjoin(curr->key, "=");
			envp[idx] = ft_strjoin(tmp, curr->value);
			(free(tmp), idx++);
		}
		curr = curr->next;
	}
	envp[idx] = NULL;
	return (envp);
}
