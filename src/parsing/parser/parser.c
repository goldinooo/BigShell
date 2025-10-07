/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 03:10:47 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/07 05:12:35 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "parsing.h"
#include "lib.h"
#include <stdbool.h>
#include <stddef.h>

void	count_cmds_and_redirs(t_token *tokens, size_t *cmds, size_t *redirs)
{
	t_token	*curr;
	size_t	cmds_local;
	size_t	redirs_local;

	curr = tokens;
	cmds_local = 0;
	redirs_local = 0;
	while (curr && curr->type != TK_PIPE)
	{
		if (curr->type != TK_WORD)
		{
			redirs_local++;
			curr = curr->next;
			if (curr)
				curr = curr->next;
		}
		else
		{
			cmds_local++;
			curr = curr->next;
		}
	}
	*cmds = cmds_local;
	*redirs = redirs_local;
}

t_token	*parse_cmds(t_shell *shell, t_token *token)
{
	size_t	redirs;
	size_t	cmds;
	t_cmd	*node;

	count_cmds_and_redirs(token, &cmds, &redirs);
	node = lst_new_cmd(fill_cmds(token, cmds));
	if (!node)
		return (NULL);
	token = skip_cmds(token, cmds);
	node->redir = fill_redirs(token, redirs);
	if (!node->redir && redirs > 0)
		return (clr_char_array(node->args), free(node), NULL);
	token = skip_redirs(token, redirs);
	shell->cmd = lst_append_cmd(shell->cmd, node);
	return (token);
}

void	parser(t_token *tokens, t_shell *shell)
{
	t_token	*curr;

	if (is_valid_syntax(tokens))
	{
		curr = tokens;
		while (curr)
		{
			if (curr->type != TK_PIPE)
			{
				curr = parse_cmds(shell, curr);
				if (!curr)
					return ; // TODO Print error here if required
			}
			else
				curr = curr->next;
		}
	}
	else
		shell->exit_status = 2;
}
