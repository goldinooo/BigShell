/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 03:17:45 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/11 04:49:23 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	child_proc(t_shell *shell, t_cmd *cmd, char *bp)
{
	char	**envp;

	envp = env_to_arr(shell->env);
	if (!envp)
		return ;
	if (!init_redirection(cmd))
	{
		clr_char_array(envp);
		exit(1);
	}
	execve(bp, cmd->args, envp);
	bprint_err((char *[]){"execve", bp, NULL}, "Error while executing cmd.");
	clr_char_array(envp);
	exit(1);
}
