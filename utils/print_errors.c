/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 00:56:25 by retahri           #+#    #+#             */
/*   Updated: 2025/10/10 05:37:08 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lib.h"
#include "minishell.h"

void	print_error_fd(char *str, t_shell *shell)
{
	ft_putstr_fd(str, STDERR_FILENO);
	shell->exit_status = EXIT_FAILURE;
}

void	print_perror(char *str, t_shell *shell)
{
	perror(str);
	shell->exit_status = EXIT_FAILURE;
}

void	exit_with_status(t_shell *shell, int status)
{
	shell->exit_status = status;
	exit(status);
}

void	print_any(char **cmd, t_shell *shell)
{
	int		idx;
	char	*buck;
	char	*tmp;

	idx = 0;
	buck = ft_strjoin(SHELL_NAME, ": ");
	while (cmd[idx])
	{
		tmp = buck;
		buck = ft_strjoin(buck, cmd[idx]);
		free(tmp);
		if (cmd[idx + 1])
		{
			tmp = buck;
			buck = ft_strjoin(buck, ": ");
			free(tmp);
		}
		idx += 1;
	}
	perror(buck);
	free(buck);
}

void	bprint_err(char **cmd, char *msg)
{
	int		idx;
	char	*buck;
	char	*tmp;

	idx = 0;
	buck = ft_strjoin(SHELL_NAME, ": ");
	while (cmd[idx])
	{
		tmp = buck;
		buck = ft_strjoin(buck, cmd[idx]);
		free(tmp);
		if (cmd[idx + 1])
		{
			tmp = buck;
			buck = ft_strjoin(buck, ": ");
			free(tmp);
		}
		idx += 1;
	}
	ft_putstr_fd(buck, 2);
	free(buck);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	ll(char **args, t_shell *shell)
{
	char	*buck;
	char	*tmp;

	if (!args[1] || !args[1][0])
		tmp = "HOME";
	else
		tmp = args[1];
	buck = ft_strjoin(PREFIX, tmp);
	buck = ft_strjoin(buck, " not set");
	printf("%s", buck);
	shell->exit_status = 1;
}
