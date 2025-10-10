/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 07:04:21 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/10 07:20:55 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "exp.h"
#include "lib.h"
#include "minishell.h"
#include "parsing.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#define ERR_MSG "not a valid identifier"

static void	no_arg_msg(t_shell *shell)
{
	t_env	*curr;

	curr = shell->env;
	while (curr)
	{
		if (curr->value)
			printf("declare -x %s=\"%s\"\n", curr->key, curr->value);
		else
			printf("declare -x %s\n", curr->key);
		curr = curr->next;
	}
}

static bool	is_valid_key(bool(vld_exp)(char, char, bool), char *key)
{
	size_t	idx;

	idx = 0;
	while (key[idx])
	{
		if (!vld_exp('$', key[idx], false))
			return (false);
		idx++;
	}
	return (true);
}

static void	assign_env(t_shell *shell, char *key, char *value)
{
	t_env	*curr;
	t_env	*node;

	if (!value || !key || !shell)
		return ;
	curr = shell->env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			if (curr->value)
				free(curr->value);
			curr->value = ft_strdup(value);
			return ;
		}
		curr = curr->next;
	}
	node = ft_lstnew_env(ft_strdup(value), ft_strdup(key));
	if (node)
		ft_lst_back_env(&shell->env, node);
}

static void	export_var(t_shell *shell, char *var)
{
	char	*has_equal;
	char	**kv;

	has_equal = ft_strchr(var, '=');
	if (has_equal)
	{
		kv = ft_split(var, '=');
		if (!kv || !*kv)
			return ;
		shell->exit_status = EXIT_FAILURE;
		if (is_valid_id(kv[0]))
		{
			assign_env(shell, kv[0], kv[1]);
			shell->exit_status = EXIT_SUCCESS;
		}
		else
			bprint_err((char *[]){"export", "'", var, "'", NULL}, ERR_MSG);
		clr_char_array(kv);
	}
	else
	{
		shell->exit_status = EXIT_FAILURE;
		if (!is_valid_key(valid_expand, var))
			bprint_err((char *[]){"export", var, NULL}, ERR_MSG);
	}
}

void	ex_export(t_shell *shell, char *argv[])
{
	size_t	idx;

	if (!argv[1])
	{
		no_arg_msg(shell);
		shell->exit_status = EXIT_FAILURE;
		return ;
	}
	idx = 0;
	while (argv[idx])
	{
		export_var(shell, argv[idx]);
		shell->exit_status = EXIT_SUCCESS;
		idx++;
	}
}
