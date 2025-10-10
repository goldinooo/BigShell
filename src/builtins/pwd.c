/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 00:54:52 by retahri           #+#    #+#             */
/*   Updated: 2025/10/10 21:48:02 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_pwd(t_shell *shell)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
		shell->exit_status = EXIT_SUCCESS;
	}
	else
	{
		perror("invalid pwd behavior");
		shell->exit_status = EXIT_SUCCESS;
	}
}
