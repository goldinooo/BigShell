/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 03:17:45 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/10 03:51:31 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_proc(t_shell *shell, int st, t_cmd *cmd, char **envp, char *bp)
{
	reset_and_catch_sig(shell, st, true);
	if (!init_redirection(cmd))
		(clr_char_array(envp), exit(1));
	execve(bp, cmd->args, envp);
	perror("execve");
	clr_char_array(envp);
	exit(1);
}
