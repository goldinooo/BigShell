/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retahri <retahri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 00:54:31 by retahri           #+#    #+#             */
/*   Updated: 2025/10/10 02:05:16 by retahri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp.h"
#include "lib.h"
#include "minishell.h"
#include <stdlib.h>

static int	is_valid_errno(char *str)
{
	int	idx;

	if (!str || !*str)
		return (0);
	idx = 0;
	if (str[idx] == '+' || str[idx] == '-')
		idx++;
	if (!str[idx])
		return (0);
	while (str[idx])
	{
		if (!ft_isdigit(str[idx]))
			return (0);
		idx++;
	}
	return (1);
}

void	ex_exit(t_shell *shell, char **args)
{
	int	arg_count;
	int	exit_code;

	if (!shell || !args)
		exit_with_status(shell, EXIT_FAILURE);
	arg_count = args_len(args);
	if (arg_count == 1)
		exit_with_status(shell, EXIT_SUCCESS);
	if (!is_valid_errno(args[1]))
	{
		print_error_fd("numeric argument required", shell);
		exit_with_status(shell, EXIT_SYNTAX);
	}
	if (arg_count > 2)
	{
		print_error_fd("exit: too many arguments", shell);
		return ;
	}
	exit_code = ft_atoi(args[1]) & 0xFF;
	exit_with_status(shell, exit_code);
}
