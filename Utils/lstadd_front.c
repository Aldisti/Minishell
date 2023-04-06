/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 08:18:47 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/04 14:36:16 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * Descritpion:	adds a new element as the first of the given list.
 * Input:	the address of the list first element pointer and 
 * 		the new element to add.
 * Output:	na.
*/
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		new->next = *lst;
		*lst = new;
	}
}

/*
 * Description:	finds the right spot to place a new element of the list
 * 		in order to preserve the list sorted
 * 		(sorted by ASCII values).
 * Input:	the list where to insert an element and the name field
 * 		of the new element (see env_set.c for further 
 * 		explanations of how works the structure used to store 
 * 		the ambient variables).
 * Output:	the list node after which has to be placed the new
 * 		elemtent; if the list hasn't nodes or the element
 * 		has to be placed as the first node a NULL pointer is
 * 		returned.
*/
t_list	*ft_lstfind_sort(t_list *lst, char *name)
{
	if (!lst)
		return (NULL);
	if (ft_strcmp(name, lst->content->name) < 0)
		return (NULL);
	while (lst->next)
	{
		if (ft_strcmp(name, lst->next->content->name) < 0)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

/*
 * Description:	insert a new element in the given list
 * 		preserving the order of the other nodes in the list
 * 		(ASCII order has been chosen).
 * Input:	the address of the list first element pointer and the new
 * 		element to place in the list.
 * Output:	na.
*/
void	ft_lst_insert(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (!tmp)
		*lst = new;
	else
	{
		tmp = ft_lstfind_sort(tmp, new->content->name);
		if (!tmp)
			ft_lstadd_front(lst, new);
		else
		{
			new->next = tmp->next;
			tmp->next = new;
		}
	}
}
