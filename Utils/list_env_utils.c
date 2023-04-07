/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:12:52 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/07 16:14:21 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
DESCRIPTION
given the node of a list and a level this function will return the env node
with that level. if it does not find the node with that level then will return
a NULL pointer
*/
t_env	*ft_get_env(t_list	*list, int lvl)
{
	t_env	*tmp;

	if (!list || lvl < 0 || !list->content)
		return (NULL);
	tmp = list->content;
	while (tmp)
	{
		if (tmp->level == lvl)
			break ;
		tmp = tmp->next;
	}
	if (!tmp || tmp->level != lvl)
		return (NULL);
	return (tmp);
}

/*
DESCRIPTION
given the node of a list and a level this function will return the env node
before the node with that level. if it does not find the node with that level
then will return a NULL pointer
*/
t_env	*ft_get_prev_env(t_list	*list, int lvl)
{
	t_env	*tmp;

	if (!list || lvl < 0 || !list->content || !list->content->next)
		return (NULL);
	tmp = list->content;
	while (tmp && tmp->next)
	{
		if (tmp->next->level == lvl)
			break ;
		tmp = tmp->next;
	}
	if (!tmp || !tmp->next || tmp->next->level != lvl)
		return (NULL);
	return (tmp);
}

/*
DESCRIPTION
given a list and the name of a variable this function returns the node of the
list with that name in the content. if it does not find any node with that name
then will return a NULL pointer
*/
t_list	*ft_get_node(t_list *list, const char *name)
{
	if (!list || !name)
		return (NULL);
	while (list)
	{
		if (list->content
			&& !ft_strncmp(list->content->name, name, ft_strlen(name)))
			break ;
		list = list->next;
	}
	return (list);
}
