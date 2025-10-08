/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:35:56 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/08 04:00:36 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>

t_cmd	*lst_new_cmd(char *args[])
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->args = args;
	node->redir = NULL;
	node->next = NULL;
	return (node);
}

t_cmd	*lst_last_cmd(t_cmd *cmds)
{
	t_cmd	*curr;

	if (!cmds)
		return (NULL);
	curr = cmds;
	while (curr->next)
		curr = curr->next;
	return (curr);
}

t_cmd	*lst_append_cmd(t_cmd *cmds, t_cmd *node)
{
	t_cmd	*last;

	if (!node)
		return (NULL);
	if (!cmds)
		cmds = node;
	else
	{
		last = lst_last_cmd(cmds);
		last->next = node;
	}
	return (cmds);
}

void	lst_clear_cmd(t_cmd *cmds)
{
	t_cmd	*curr;
	t_cmd	*next;

	if (!cmds)
		return ;
	curr = cmds;
	while (curr)
	{
		next = curr->next;
		clr_char_array(curr->args);
		lst_clear_redirs(curr->redir);
		free(curr);
		curr = next;
	}
}
