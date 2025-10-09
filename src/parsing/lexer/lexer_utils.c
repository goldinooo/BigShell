/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 22:56:47 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/08 00:34:04 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lib.h"

t_token	*create_token(char *value, t_tktype type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

size_t	skip_spaces(char *input, size_t idx)
{
	while (is_space(input[idx]))
		idx++;
	return (idx);
}

size_t	get_word_end(char *input, size_t start)
{
	size_t	idx;
	char	quote;

	idx = start;
	quote = 0;
	while (input[idx])
	{
		if ((input[idx] == SQUOTE || input[idx] == DQUOTE) && !quote)
			quote = input[idx];
		else if (quote == input[idx])
			quote = 0;
		else if (!quote)
		{
			if (is_op(input[idx]) || is_space(input[idx]))
				break ;
		}
		idx++;
	}
	return (idx);
}
