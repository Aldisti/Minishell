/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:30:42 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/14 11:45:30 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
this function is only for debug!!!
DESCRIPTION
given a node of the list this function will print all the env connected to that
node
*/
void	ft_print_env(t_list *lst)
{
	t_env	*env;

	if (!lst || !lst->content)
		return ;
	env = lst->content;
	while (env)
	{
		printf("ENV: |%s| - |%s| - %d\n", env->name, env->value, env->level);
		env = env->next;
	}
}

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
	new->value = value;
	new->level = lvl;
	new->set = 1;
	new->next = NULL;
	return (new);
}

void	ft_set_name_value(t_shell *shell, char **name, char **value, char *cmd)
{
	(*name) = ft_get_name(cmd);
	if (!(*name))
		ft_die(shell, 1, 12);
	if (!ft_in('=', cmd))
	{
		*value = ft_strjoin(*name, "=");
		if (!(*value))
			ft_die(shell, 1, 12);
		ft_free((void **)name);
		*name = *value;
		*value = NULL;
	}
	else
	{
		(*value) = ft_get_value(cmd, *name, 0);
		if (!(*value))
		{
			ft_free((void **)name);
			ft_die(shell, 1, 12);
		}
	}
}

void	ft_do_export1(t_shell *shell, t_env **new_env, char *name, int lvl)
{
	t_list	*list;

	list = ft_get_node(shell->list, name);
	if (!list)
	{
		list = ft_lstnew(*new_env);
		if (!list)
			ft_die(shell, ft_free_env(new_env) + 1, 12);
		ft_lst_insert(&(shell->list), list);
	}
	else if (list->content && list->content->level > lvl)
	{
		(*new_env)->next = list->content;
		list->content = (*new_env);
	}
	else
		ft_do_export2(list, new_env, lvl);
}

void	ft_do_export2(t_list *list, t_env **new_env, int lvl)
{
	t_env	*env;

	env = ft_get_env(list, lvl);
	if (!env)
		ft_env_insert(&(list->content), (*new_env));
	else
	{
		while (env && env->level != lvl)
			env = env->next;
		if (env && (*new_env)->value && env->level == lvl)
		{
			ft_free((void **)&(env->value));
			env->value = ft_strdup((*new_env)->value);
		}
		ft_free_env(new_env);
	}
}
