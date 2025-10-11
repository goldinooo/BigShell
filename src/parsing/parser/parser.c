/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 03:10:47 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/11 04:50:45 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static t_token	*skip_cmds(t_token *tokens, size_t cmds)
{
	t_token	*curr;

	curr = tokens;
	while (cmds > 0 && curr)
	{
		if (curr->type == TK_WORD)
		{
			cmds--;
			curr = curr->next;
		}
		else
		{
			curr = curr->next;
			if (curr)
				curr = curr->next;
		}
	}
	return (curr);
}

static t_token	*skip_redirs(t_token *tokens, size_t redirs)
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

static void	count_cmds_and_redirs(t_token *tokens, size_t *cmds, size_t *redirs)
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

static t_token	*parse_cmds(t_shell *shell, t_token *token)
{
	size_t	redirs;
	size_t	cmds;
	t_cmd	*node;
	t_token	*start_token;

	start_token = token;
	count_cmds_and_redirs(token, &cmds, &redirs);
	node = lst_new_cmd(fill_cmds(token, cmds));
	if (!node)
		return (NULL);
	token = skip_cmds(token, cmds);
	node->redir = fill_redirs(start_token, redirs);
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
					return ;
			}
			else
				curr = curr->next;
		}
	}
	else
		shell->exit_status = EXIT_SYNTAX;
}
