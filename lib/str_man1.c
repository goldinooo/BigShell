/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_man1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retahri <retahri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 00:53:46 by retahri           #+#    #+#             */
/*   Updated: 2025/10/10 03:09:22 by retahri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	ft_atoi(const char *str)
{
	int		result;
	size_t	idx;
	int		sign;

	result = 0;
	sign = 1;
	idx = 0;
	while (is_space(str[idx]))
		idx++;
	if (str[idx] == '-' || str[idx] == '+')
	{
		if (str[idx] == '-')
			sign *= -1;
		idx++;
	}
	while (str[idx] >= 48 && str[idx] <= 57)
	{
		result = (result * 10) + (str[idx] - 48);
		idx++;
	}
	return (result * sign);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
