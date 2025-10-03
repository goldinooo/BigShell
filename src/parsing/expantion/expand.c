/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 01:12:11 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/01 02:40:19 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exp.h"
#include "lexer.h"
#include "minishell.h"
#include "parsing.h"
#include "utils.h"
#include <stdlib.h>

int expander_magic(t_exp *exp, char *value, int i, t_shell *shell)
{
	char *exit_status;

	exp->start_pos = ++i;
	if(value[i] == '?')
	{
		exit_status = ft_itoa(shell->exit_status);
		exp->output = ft_strjoin(exp->output, exit_status);
		free(exit_status);
	}
	else 
	{
		while(ft_isalnum(value[i]) || value[i] == '_')
			i++;
		exp->var = ft_substr(value, exp->start_pos, i - exp->start_pos);
		exp->var = value_from_env(exp->var, shell->env);
		if(exp->var)
			exp->output = ft_strjoin(exp->output, exp->var);
		exp->var = NULL;
		i--; // incremented in expand_var
	}
	return (i);
}
void	skip_and_join(t_exp *exp, char *value, int i)
{
	if (value[i] == '$' && !exp->is_dquote && !exp->is_squote)
	{
		if (ft_isdigit(value[i + 1]))
			return; // skip this char
		else if (value[i + 1] == SQUOTE || value[i + 1] == DQUOTE)
			return;
	}
	exp->output = app_char(exp->output, value[i]);
}


char *expand_var(t_shell *shell, char *value)
{
	t_exp	exp;
	int 	idx;
	
	idx = 0;
	init_exp(&exp);
	while(value[idx])
	{
		if (value[idx] == SQUOTE && !exp.is_dquote)
			handle_quotes(&exp, value[idx], true);
		else if (value[idx] == DQUOTE && !exp.is_squote)
			handle_quotes(&exp, value[idx], false);
		else if (valid_expand(value[idx], value[idx + 1], exp.is_squote))
			idx = expander_magic(&exp, value, idx, shell);
		else
			skip_and_join(&exp, value, idx);
		idx++;
	}
	free(value);
	return (exp.output);
}

void	exp_redir(t_redir *red, t_shell *shell)
{
	while(red)
	{
		if(red->type != TK_HEREDOC)
			red->file = expand_var(shell, red->file);
		else if (red->type == TK_HEREDOC)
			should_heredoc_expand(red);
		red = red->next;
	}
}

void	expand(t_shell *shell)
{
	t_cmd	*ptr;
	char	*value;
	int 	 idx;

	ptr = shell->cmd;
	while (ptr)
	{
		idx = 0;
		while (ptr->args[idx])
		{
			value = expand_var(shell, ptr->args[idx]);
			if (multiple_args(value, false, false, false))
				ptr->args = append_args(ptr->args, value, &idx, 0);
			else
			{
				ptr->args[idx] = value;
				idx++;
			}
		}
		exp_redir(ptr->redir, shell);
		ptr = ptr->next;
	}
}
