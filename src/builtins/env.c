/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retahri <retahri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 00:54:26 by retahri           #+#    #+#             */
/*   Updated: 2025/10/10 02:03:56 by retahri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "lib.h"
#include "minishell.h"
#include <stdlib.h>

void	ex_env(t_shell *shell)
{
	t_env	*cpy;

	cpy = shell->env;
	while (cpy)
	{
		if (cpy->value)
		{
			ft_putstr_fd(cpy->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(cpy->value, 1);
			write(1, "\n", 1);
		}
		cpy = cpy->next;
	}
	shell->exit_status = EXIT_SUCCESS;
}
