/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:21:59 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/11 06:30:29 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_cmds(t_token *tokens, size_t cmds)
{
	t_token	*curr;
	char	**args;
	size_t	idx;

	args = malloc(sizeof(char *) * (cmds + 1));
	if (!args)
		return (NULL);
	idx = 0;
	curr = tokens;
	while (idx < cmds && curr && curr->type != TK_PIPE)
	{
		if (curr->type == TK_WORD)
		{
			args[idx] = ft_strdup(curr->value);
			idx++;
			curr = curr->next;
		}
		else
		{
			curr = curr->next;
			if (curr)
				curr = curr->next;
		}
	}
	return (args[idx] = NULL, args);
}

t_redir	*fill_redirs(t_token *tokens, size_t redirs)
{
	t_redir	*redir;
	t_redir	*node;
	t_token	*curr;
	char	*value;

	redir = NULL;
	curr = tokens;
	while (curr && redirs > 0)
	{
		if (curr->type == TK_WORD)
		{
			curr = curr->next;
			continue ;
		}
		value = ft_strdup(curr->next->value);
		if (!value)
			return (lst_clear_redirs(redir), NULL);
		node = lst_new_redir(curr->type, value);
		if (!node)
			return (free(value), lst_clear_redirs(redir), NULL);
		redir = lst_append_redirs(redir, node);
		redirs--;
		curr = curr->next->next;
	}
	return (redir);
}
