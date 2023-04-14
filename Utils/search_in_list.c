/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:48:15 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/14 13:44:24 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
NAME: is the name of the variable you want to search
LVL: is the number of the subshell where you want to search the variable
RETURN
returns the pointer to the node of the variable at the level lvl,
if there's not the level you are searching for it will return the
closest smaller level to lvl. If the name is not in the list, return
value will be 0
*/
t_env	*ft_search_in_list(t_list *list, char *name, int lvl)
{
	t_env	*tmp;

	if (!list || !list->content)
		return (0);
	while (list->next && ft_strncmp(list->content->name, name, ft_strlen(name)))
		list = list->next;
	if (ft_strncmp(list->content->name, name, ft_strlen(name)) && )
		return (0);
	tmp = list->content;
	while (tmp && tmp->next && tmp->level != lvl)
		tmp = tmp->next;
	if (tmp && tmp->level > lvl)
		return (NULL);
	return (tmp);
}
