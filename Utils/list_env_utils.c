/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:12:52 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/21 11:11:23 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * Descritpion:	adds a new element as the first of the given list.
 * Input:	the address of the list first element pointer and 
 * 		the new element to add.
 * Output:	na.
*/
void	ft_envadd_front(t_env **env, t_env *new)
{
	if (!env || !new)
		return ;
	if (!(*env))
		*env = new;
	else
	{
		new->next = *env;
		*env = new;
	}
}

/*
 * Description:	finds the right spot to place a new element of the env
 * 		in order to preserve the env sorted
 * 		(sorted by level values).
 * Input:	the env where to insert an element and the level field
 * 		of the new element (see env_set.c for further 
 * 		explanations of how works the structure used to store 
 * 		the ambient variables).
 * Output:	the env node after which has to be placed the new
 * 		elemtent; if the envs hasn't nodes or the element
 * 		has to be placed as the first node a NULL pointer is
 * 		returned.
*/
t_env	*ft_envfind_sort(t_env *env, int lvl)
{
	if (!env)
		return (NULL);
	if (env->level > lvl)
		return (NULL);
	while (env->next)
	{
		if (env->next->level > lvl)
			return (env);
		env = env->next;
	}
	return (env);
}

/*
 * Description:	insert a new element in the given env list
 * 		preserving the order of the other nodes in the env list
 * 		(number order has been chosen).
 * Input:	the address of the envlist first element pointer and the new
 * 		element to place in the list.
 * Output:	na.
*/
void	ft_env_insert(t_env **env, t_env *new)
{
	t_env	*tmp;

	tmp = *env;
	if (!tmp)
		*env = new;
	else
	{
		tmp = ft_envfind_sort(tmp, new->level);
		if (!tmp)
			ft_envadd_front(env, new);
		else
		{
			new->next = tmp->next;
			tmp->next = new;
		}
	}
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
		if (list->content && ft_strlen(list->content->name) - 1 == ft_strlen(name)
			&& !ft_strncmp(list->content->name, name, ft_strlen(name)))
			break ;
		list = list->next;
	}
	return (list);
}

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
