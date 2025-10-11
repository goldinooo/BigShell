/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 04:57:44 by retahri           #+#    #+#             */
/*   Updated: 2025/10/11 06:17:41 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_cd(t_shell *shell, char **args)
{
	char	*target;

	target = NULL;
	shell->exit_status = EXIT_SUCCESS;
	target = value_from_env(ft_strdup("HOME"), shell->env);
	if (!target && !args[1])
	{
		shell->exit_status = 1;
		ll(args, shell);
		return ;
	}
	if (!args[1] || (args[1] && !args[1][0]))
	{
		if (chdir(target) != 0)
			ll(args, shell);
		return ;
	}
	if (chdir(args[1]) != 0)
		print_error_fd("Minishell: cd: No such file or directory\n", shell);
}
