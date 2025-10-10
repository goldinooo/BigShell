/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:27:27 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/10 05:10:53 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "lexer.h"
#include "minishell.h"
#include "parsing.h"

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void	clr_char_array(char **array)
{
	size_t	idx;

	if (!array)
		return ;
	idx = 0;
	while (array[idx])
		free(array[idx++]);
	free(array);
}

void	clean_shell(t_shell *shell)
{
	ft_lst_clear_env(&shell->env);
	lst_clear_cmd(shell->cmd);
}
