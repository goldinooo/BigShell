/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_unst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 00:56:18 by retahri           #+#    #+#             */
/*   Updated: 2025/10/11 00:16:59 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_id(char *str)
{
	int	idx;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	idx = 1;
	while (str[idx])
	{
		if (!ft_isalnum(str[idx]) && str[idx] != '_')
			return (0);
		idx++;
	}
	return (1);
}
