/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:26:02 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/01 22:31:22 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*skip_cmds(t_token *tokens, size_t cmds)
{
	t_token	*curr;

	curr = tokens;
	while (cmds > 0 && curr)
	{
		if (curr->type == TK_WORD)
			cmds--;
		else
		{
			// Skip redirection operator and its filename
			curr = curr->next;
			if (curr)
				curr = curr->next;
			continue;
		}
		curr = curr->next;
	}
	return (curr);
}

t_token	*skip_redirs(t_token *tokens, size_t redirs, size_t cmds)
{
	t_token	*curr;

	curr = tokens;
	while (redirs > 0 && curr)
	{
		// Each redirection is 2 tokens: operator + filename
		curr = curr->next;
		if (curr)
			curr = curr->next;
		redirs--;
	}
	// Now we should be at a pipe or end of tokens
	if (curr && curr->type == TK_PIPE)
		curr = curr->next;
	return (curr);
}
