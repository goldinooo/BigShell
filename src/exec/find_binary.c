/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 03:18:46 by abraimi           #+#    #+#             */
/*   Updated: 2025/10/04 03:44:26 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "exec.h"
#include "lib.h"
#include "parsing.h"
#include <stddef.h>
#include <unistd.h>

static char	*crawl_paths(char *paths[], char *bin)
{
	char	*abs_path;
	char	*tmp;
	size_t	idx;

	idx = 0;
	while (paths[idx])
	{
		abs_path = ft_strjoin(paths[idx], "/");
		if (!abs_path)
			return (NULL);
		tmp = abs_path;
		abs_path = ft_strjoin(abs_path, bin);
		free(tmp);
		if (!abs_path)
			return (NULL);
		if (!access(abs_path, X_OK | F_OK))
			return (abs_path);
		free(abs_path);
		idx++;
	}
	return (NULL);
}

char	*get_bin_path(char *bin, t_env *env)
{
	char	**paths;
	char	*tmp;

	if (!bin)
		return (NULL);
	if (ft_strchr(bin, '/'))
	{
		if (!access(bin, X_OK | F_OK))
			return (ft_strdup(bin));
		return (NULL);
	}
	tmp = value_from_env(ft_strdup("PATH"), env);
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp, ':');
	if (!paths)
		return (NULL);
	tmp = crawl_paths(paths, bin);
	return (clr_char_array(paths), tmp);
}
