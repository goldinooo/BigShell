/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 22:56:54 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/03 21:15:34 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lib.h"

t_tktype	get_operator_type(char *input, size_t idx)
{
	if (input[idx] == PIPE)
		return (TK_PIPE);
	else if (input[idx] == REDIR_IN)
	{
		if (input[idx + 1] == REDIR_IN)
			return (TK_HEREDOC);
		return (TK_REDIR_IN);
	}
	else if (input[idx] == REDIR_OUT)
	{
		if (input[idx + 1] == REDIR_OUT)
			return (TK_APPEND_OUT);
		return (TK_REDIR_OUT);
	}
	return (TK_WORD);
}

size_t	process_operator(char *input, size_t idx, t_token **tokens)
{
	t_tktype	type;
	char		*op_value;
	t_token		*new_token;

	type = get_operator_type(input, idx);
	if (type == TK_HEREDOC || type == TK_APPEND_OUT)
	{
		op_value = ft_substr(input, idx, 2);
		idx += 2;
	}
	else
	{
		op_value = ft_substr(input, idx, 1);
		idx += 1;
	}
	new_token = create_token(op_value, type);
	if (new_token)
		add_token(tokens, new_token);
	free(op_value);
	return (idx);
}

size_t	process_word(char *input, size_t idx, t_token **tokens)
{
	size_t	end;
	char	*word;
	t_token	*new_token;

	end = get_word_end(input, idx);
	word = ft_substr(input, idx, end - idx);
	new_token = create_token(word, TK_WORD);
	if (new_token)
		add_token(tokens, new_token);
	free(word);
	return (end);
}

void	lexer(char *input, t_token **tokens)
{
	size_t	idx;

	idx = 0;
	*tokens = NULL;
	while (input[idx])
	{
		idx = skip_spaces(input, idx);
		if (!input[idx])
			break;
		if (is_op(input[idx]))
			idx = process_operator(input, idx, tokens);
		else
			idx = process_word(input, idx, tokens);
	}
}
