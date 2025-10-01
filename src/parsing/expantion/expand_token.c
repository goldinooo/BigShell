/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 02:20:19 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/01 02:53:33 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp.h"


// TODO STOPPED IN EXPANDING TOKENS
char	*expand_token(char *key, t_env *env)
{
	bool	is_in_dquotes;

	is_in_dquotes = false;
	while (*key)
	{
		if (*key == '\'' && !is_in_dquotes)
			// handle_squotes();
			return (NULL);
		else if (*key == '$')
			// handle_env_key();
			return (NULL);
		else
		{
			// if (*key == '"')

		}
	}
	return (NULL);
}
