/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:26:02 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/07 04:51:33 by abraimi          ###   ########.fr       */
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
			(cmds--, curr = curr->next);
		else
		{
			curr = curr->next;
			if (curr)
				curr = curr->next;
		}
	}
	return (curr);
}

t_token	*skip_redirs(t_token *tokens, size_t redirs)
{
	t_token	*curr;

	curr = tokens;
	while (redirs > 0 && curr)
	{
		curr = curr->next;
		if (curr)
			curr = curr->next;
		redirs--;
	}
	if (curr && curr->type == TK_PIPE)
		curr = curr->next;
	return (curr);
}
