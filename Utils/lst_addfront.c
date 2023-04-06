/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_addfront.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 08:18:47 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/05 11:18:21 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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