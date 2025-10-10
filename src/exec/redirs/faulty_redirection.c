/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   faulty_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 22:03:44 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/03 23:32:21 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lib.h"
#include "parsing.h"
#include <stdbool.h>

bool	is_faulty_redir(t_redir *redir)
{
	char	*filename;

	if (redir->type == TK_HEREDOC && redir->shouldexpand)
	{
		filename = redir->file;
		if (!filename || !*filename)
			return (true);
			// TODO Print an error message in case the filename is either empty or NULL
		while (is_space(*filename))
			filename++;
		while (*filename)
		{
			if (is_space(*filename) && *(filename + 1) && !is_space(*(filename
						+ 1)))
			{
				// TODO PRINT THE ERROR MESSAGE FOR faulty filename
				return (true);
			}
		}
	}
	return (false);
}
