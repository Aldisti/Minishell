/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:26:10 by mpaterno          #+#    #+#             */
/*   Updated: 2023/01/18 21:37:08 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **alst, void (*del)(void *))
{
	t_list	*current;
	t_list	*temp;

	if (!alst || !del)
		return ;
	temp = (*alst);
	while (temp)
	{
		current = (temp)->next;
		(*del)((temp)->content);
		free(temp);
		temp = current;
	}
	*alst = 0;
}
