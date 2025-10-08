/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:33:37 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/08 00:33:38 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdbool.h>

bool	is_pipe(char ch)
{
	return (ch == PIPE);
}

bool	is_op(char ch)
{
	return (is_pipe(ch) || ch == REDIR_IN || ch == REDIR_OUT);
}

bool	is_redir(char ch, int dir)
{
	if (dir == 0)
		return (ch == REDIR_IN);
	else if (dir == 1)
		return (ch == REDIR_OUT);
	return (false);
}
