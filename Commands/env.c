/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:18:10 by afraccal          #+#    #+#             */
/*   Updated: 2023/04/11 22:32:32 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env(t_shell	*shell, int lvl)
{
	t_list	*lst;
	t_env	*tmp;

	lst = shell->list;
	while (lst)
	{
		tmp = ft_search_in_list(lst, lst->content->name, lvl);
		if (tmp && tmp->name && tmp->value)
			printf("%s%s\n", tmp->name, tmp->value);
		lst = lst->next;
	}
	return (0);
}
