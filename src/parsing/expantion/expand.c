/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 01:12:11 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/01 02:40:19 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp.h"

char	*expand_tilde(char *key, t_env *env)
{
	char	*value;

	value = value_from_env(ft_strdup(key), env);
	if (!value)
		return (ft_strdup(key));
	if (!key[1])
		return (ft_strdup(value));
	else
		return (ft_strjoin(value, key + 1));

}

bool	expand(t_token *tokens, t_env *env)
{
	t_token	*current;
	t_token	*prev;
	char	*value;

	current = tokens;
	prev= NULL;
	while (current)
	{
		if (current->type == TK_WORD
			&& !(prev && (prev->type == TK_HEREDOC)))
		{
			value = current->value;
			if (value[0] == '~' && (!value[1] || value[1] == '/'))
				(free(current->value),
					current->value = expand_tilde(value, env));
			else
				(free(current->value),
					current->value = expand_token(value, env));
			if (!current->value)
				return (false);
		}
		prev = current;
		current = current->next;
	}
	return (true);
}
