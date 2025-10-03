/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:52:59 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/03 08:16:26 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clr_char_array(char **array)
{
	size_t	idx;

	if (!array)
		return ;
	idx = 0;
	while (array[idx])
		free(array[idx++]);
	free(array);
}
