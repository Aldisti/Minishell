/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:26:41 by mpaterno          #+#    #+#             */
/*   Updated: 2023/01/19 10:16:21 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*temp;
	t_list	*ret;

	if (!lst || !f || !del)
		return (NULL);
	temp = lst;
	new_lst = ft_lstnew(f(temp->content));
	ret = new_lst;
	while (temp->next)
	{
		new_lst->next = ft_lstnew(f(temp->next->content));
		new_lst = new_lst->next;
		temp = temp->next;
	}
	return (ret);
}
