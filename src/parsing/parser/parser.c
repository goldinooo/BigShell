/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 03:10:47 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/01 22:31:14 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "parsing.h"
#include "utils.h"
#include <stddef.h>

void	cmds_and_redirs(t_token *tokens, size_t *cmds, size_t *redirs)
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
			curr = curr->next; // skip redirection operator
			if (curr)
				curr = curr->next; // skip filename
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

void	parser(t_token *tokens, t_shell *shell)
{
	size_t	redirs;
	size_t	cmds;
	t_cmd	*node;
	t_token	*curr;

	if (is_valid_syntax(tokens))
	{
		curr = tokens;
		while (curr)
		{
			if (curr->type != TK_PIPE)
			{
				cmds_and_redirs(curr, &cmds, &redirs);
				// TODO j = cmds -1, to know how many commads to skip before getting to the redir
				node = lst_new_cmd(fill_cmds(curr, cmds));
				if (!node)
					return ; // TODO Add a proper malloc handling.
				curr = skip_cmds(curr, cmds);
				node->redir = fill_redirs(curr, redirs);
				if (!node->redir && redirs > 0)
				{
					clr_char_array(node->args);
					free(node);
					return ;
				}
				curr = skip_redirs(curr, redirs, cmds);
				shell->cmd = lst_append_cmd(shell->cmd, node);
			}
			else
				curr = curr->next;
		}
	}
	else
		// TODO Add the exit code to the exit_status variable
		return ; //! Remove me
}
