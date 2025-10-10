/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraimi <abraimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 00:55:22 by retahri           #+#    #+#             */
/*   Updated: 2025/10/10 07:26:07 by abraimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>

t_env	*ft_lstnew_env(char *value, char *key)
{
	t_env	*node;

	node = NULL;
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_env	*ft_lstlast_env(t_env *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
	{
		list = list->next;
	}
	return (list);
}

void	ft_lst_clear_env(t_env **lst)
{
	t_env	*tmp;
	t_env	*curr;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp != NULL)
	{
		curr = tmp;
		tmp = tmp->next;
		free(curr->key);
		free(curr->value);
		free(curr);
	}
	*lst = NULL;
}

void	ft_lst_back_env(t_env **lst, t_env *node)
{
	t_env	*tail;

	if (!lst || !node)
		return ;
	if (*lst == NULL)
		*lst = node;
	else
	{
		tail = ft_lstlast_env(*lst);
		tail->next = node;
	}
}
