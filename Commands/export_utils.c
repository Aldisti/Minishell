/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:30:42 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/08 09:32:23 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
if the malloc fails this function does the free of name and value
*/
t_env	*ft_env_new(char *name, char *value, int lvl)
{
	t_env	*new;

	new = (t_env *) malloc (sizeof(t_env));
	if (!new)
	{
		ft_free((void **)&name);
		ft_free((void **)&value);
		return (0);
	}
	new->name = name;
	new->level = lvl;
	new->value = value;
	new->set = 1;
	new->next = 0;
	return (new);
}

int	ft_if2(t_list *list, t_env *env, t_env *new_env, int lvl)
{
	if (env && env->level < lvl && env->next->level > lvl)
	{
		new_env->next = env->next;
		env->next = new_env;
		return (4);
	}
	else if (env && list->content->level > lvl)
	{
		new_env->next = list->content->next;
		list->content->next = new_env;
		return (5);
	}
	else
		return (0);
}

int	ft_if1(t_list *list, t_env *new_env)
{
	t_env	*env;

	env = ft_search_in_list(list, new_env->name, new_env->level);
	if (env && env->level == new_env->level)
	{
		ft_free((void **)&(env->value));
		if (new_env->value)
			env->value = ft_strdup(new_env->value);
		else
			env->value = 0;
		ft_free_env(&new_env);
		return (2);
	}
	else if (env && env->level < new_env->level && !env->next)
	{
		env->next = new_env;
		return (3);
	}
	else
		return (ft_if2(list, env, new_env, new_env->level));
}


