/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retahri <retahri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 04:57:44 by retahri           #+#    #+#             */
/*   Updated: 2025/10/10 05:06:40 by retahri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exp.h"
#include "lib.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	ex_cd(t_shell *shell, char **args)
{
	char	*target;

	target = NULL;
	shell->exit_status = EXIT_SUCCESS;
	target = value_from_env(ft_strdup("HOME"), shell->env);
	if (!target && !args[1])
	{
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
		print_any(args, shell);
}
