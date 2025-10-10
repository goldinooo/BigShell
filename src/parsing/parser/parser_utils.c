/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:26:02 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/10 03:28:54 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

#define SYNTAX_ERR "syntax error near unexpected token `newline'"

bool	is_valid_pipe(t_token *prev, t_token *curr)
{
	if (curr->type == TK_PIPE)
	{
		if (prev->type != TK_WORD)
		{
			bprint_err("|", SYNTAX_ERR);
			return (false);
		}
		if (!curr->next)
		{
			bprint_err("|", SYNTAX_ERR);
			return (false);
		}
	}
	return (true);
}

bool	is_valid_redir(t_token *curr)
{
	unsigned int	type;

	type = curr->type;
	if (type == TK_REDIR_IN || type == TK_REDIR_OUT || type == TK_APPEND_OUT
		|| type == TK_HEREDOC)
	{
		if (!curr->next)
		{
			bprint_err(NULL, SYNTAX_ERR);
			return (false);
		}
		else if (curr->next->type != TK_WORD)
		{
			bprint_err(NULL, SYNTAX_ERR);
			return (false);
		}
	}
	return (true);
}
