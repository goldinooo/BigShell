/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 00:54:57 by retahri           #+#    #+#             */
/*   Updated: 2025/10/10 21:48:11 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_env_key(char *key, t_env **env)
{
	t_env	*curr;
	t_env	*prev;

	if (!env || !*env)
		return ;
	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			if (curr->value)
				free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

static void	unset_var(char *arg, t_shell *shell)
{
	if (is_valid_id(arg))
		clean_env_key(arg, &shell->env);
	else
	{
		ft_putstr_fd("Minishell: unset: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(" : not a valid identifier\n", STDERR_FILENO);
		shell->exit_status = 1;
	}
}

void	ex_unset(t_shell *shell, char **args)
{
	int	idx;

	if (!shell || !shell->env || !args || !args[1])
		return ;
	idx = 1;
	while (args[idx])
	{
		unset_var(args[idx], shell);
		idx++;
	}
}
