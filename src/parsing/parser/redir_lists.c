/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:01:34 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/01 21:58:24 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_redir	*lst_new_redir(size_t type, char *file)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->type = type;
	node->file = file;
	node->heredoc_fd = 0;
	node->shouldexpand = true;
	node->next = NULL;
	return (node);
}

t_redir	*lst_last_redir(t_redir *redirs)
{
	t_redir	*curr;

	if (!redirs)
		return (NULL);
	curr = redirs;
	while (curr->next)
		curr = curr->next;
	return (curr);
}

t_redir	*lst_append_redirs(t_redir *redirs, t_redir *node)
{
	t_redir	*last;

	if (!node)
		return (NULL);
	if (!redirs)
		redirs = node;
	else
	{
		last = lst_last_redir(redirs);
		last->next = node;
	}
	return (redirs);
}

void	lst_clear_redirs(t_redir *redirs)
{
	t_redir	*curr;
	t_redir	*next;

	if (!redirs)
		return ;
	curr = redirs;
	while (curr)
	{
		next = curr->next;
		free(curr->file);
		free(curr);
		curr = next;
	}
}
