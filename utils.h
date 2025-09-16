/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reda <reda@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:00:00 by reda              #+#    #+#             */
/*   Updated: 2025/09/16 00:00:00 by reda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*
 * String splitting utilities
 */

/* Split string by delimiter, returns NULL-terminated array */
char	**ft_split(char const *s, char c);

/* Free the result of ft_split */
void	free_split_result(char **split);

/* Count elements in split result */
int		split_count(char **split);

#endif
