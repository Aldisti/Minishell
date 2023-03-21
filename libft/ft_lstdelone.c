/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 08:53:57 by gpanico           #+#    #+#             */
/*   Updated: 2023/01/20 09:39:09 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_destroy_lst(t_list **lst)
{
	t_list	*tmp;

	if (*lst)
	{
		tmp = *lst;
		*lst = NULL;
		ft_memset(tmp, 0, sizeof(t_list));
		free(tmp);
	}
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	(*del)(lst->content);
	ft_destroy_lst(&lst);
}
