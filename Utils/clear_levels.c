/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_levels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:27:53 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/18 10:27:54 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_envdel(t_env *env)
{
	t_env	*previous;

	while (env)
	{
		previous = env;
		env = env->next;
		ft_free((void **) &previous->name);
		ft_free((void **) &previous->value);
		ft_free((void **) &previous);
	}
}

void	ft_first_node(t_list **list, int lvl)
{	
	t_env	*previous;
	t_env	*tmp_elem;
	t_list	*tmp_node;

	tmp_elem = (t_env *)(*list)->content;
	if (tmp_elem->level >= lvl)
	{
		ft_envdel(tmp_elem);
		tmp_node = *list;
		*list = (*list)->next;
		ft_free((void **) &tmp_node);
	}
	else
	{
		while (tmp_elem->next && tmp_elem->next->level < lvl)
			tmp_elem = tmp_elem->next;
		if (tmp_elem->next)
		{
			previous = tmp_elem;
			tmp_elem = tmp_elem->next;
			previous->next = NULL;
			ft_envdel(tmp_elem);
		}
	}
}

void	ft_in_node(t_list **node, t_list **prev_node, int lvl)
{
	t_env	*previous;
	t_env	*tmp_elem;

	tmp_elem = (t_env *)(*node)->content;
	if (tmp_elem->level >= lvl)
	{
		ft_envdel(tmp_elem);
		(*prev_node)->next = (*node)->next;
		ft_free((void **) node);
		*node = (*prev_node)->next;
	}
	else
	{
		while (tmp_elem->next && tmp_elem->next->level < lvl)
			tmp_elem = tmp_elem->next;
		if (tmp_elem->next)
		{
			previous = tmp_elem;
			tmp_elem = tmp_elem->next;
			previous->next = NULL;
			ft_envdel(tmp_elem);
		}
		*prev_node = *node;
		*node = (*node)->next;
	}
}

void	ft_clear_levels(t_shell	*shell, int lvl)
{
	t_list	*previous_node;
	t_list	*tmp_node;

	if (!shell->list)
		return ;
	ft_first_node(&(shell->list), lvl);
	previous_node = shell->list;
	tmp_node = shell->list->next;
	while (tmp_node)
		ft_in_node(&tmp_node, &previous_node, lvl);
}
