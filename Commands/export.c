/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:16:39 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/06 14:42:12 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
cerco il nodo della lista corrispondente al nome
	se non lo trovo
		creo il nuovo nodo e uso insert
	se lo trovo
		creo un nuovo nodo
		cerco il nodo corrispondente al livello
			se trovo il nodo con lo stesso livello
				modifico la variabile value
			se non lo trovo
				lo inserisco nel nodo della lista
			se trovo un livello maggiore
				inserisco il nodo prima di quello trovato
			se trovo un livello inferiore o un nodo nullo
				inserisco il nodo dopo quello trovato o alla fine
*/

int	ft_print_export(t_shell *shell, int lvl)
{
	t_list	*lst;
	t_env	*tmp;

	lst = shell->list;
	while (lst)
	{
		tmp = ft_search_in_list(lst, lst->content->name, lvl);
		if (tmp && tmp->name && tmp->value)
			printf("declare -x %s%s\n", tmp->name, tmp->value);
		else if (tmp && tmp->name && !tmp->value)
		{
			tmp->name[ft_strlen(tmp->name) - 1] = 0;
			printf("declare -x %s\n", tmp->name);
			tmp->name[ft_strlen(tmp->name)] = '=';
		}
		lst = lst->next;
	}
	return (5);
}

t_env	*ft_env_new(char *name, char *value, int lvl)
{
	t_env	*new;

	new = (t_env *) malloc (sizeof(t_env));
	if (!new)
		return (0);
	new->name = name;
	new->level = lvl;
	new->value = value;
	new->set = 1;
	new->next = 0;
	return (new);
}

int	ft_export(t_shell *shell, char **cmd, int lvl)
{
	t_list	*list;
	t_list	*new_lst;
	t_env	*env;
	t_env	*new_env;
	char	*name;
	char	*value;

	name = 0;
	value = 0;
	if (!cmd[1])
		return (ft_print_export(shell, lvl));
	name = ft_get_name(cmd[1]);
	if (!name)
		return (-1);
	if (name[ft_strlen(name) - 1] != '=')
	{
		value = ft_strjoin(name, "=");
		ft_free((void **)&name);
		name = value;
		value = 0;
	}
	else
	{
		value = ft_get_value(cmd[1], name, 0);
		if (!value)
		{
			ft_free((void **)&name);
			return (-1);
		}
		ft_remove_quotes(&value);
	}
	list = shell->list;
	while (list && ft_strcmp(list->content->name, name))
		list = list->next;
	new_env = ft_env_new(name, value, lvl);
	if (!new_env)
	{
		ft_free((void **)&name);
		ft_free((void **)&value);
		return (-2);
	}
	if (!list)
	{
		new_lst = ft_lstnew(new_env);
		if (!new_lst)
			return (ft_free_env(&new_env));
		ft_lst_insert(&(shell->list), new_lst);
		return (1);
	}
	env = ft_search_in_list(list, name, lvl);
	// modifico solo value
	if (env && env->level == lvl)
	{
		ft_free((void **)&(env->value));
		if (value)
			env->value = ft_strdup(value);
		else
			env->value = 0;
		ft_free_env(&new_env);
		return (2);
	}
	// aggiungo alla fine
	else if (env && env->level < lvl && !env->next)
	{
		env->next = new_env;
		return (4);
	}
	// aggiungo in mezzo
	else if (env && env->level < lvl && env->next->level > lvl)
	{
		new_env->next = env->next;
		env->next = new_env;
		return (3);
	}
	// aggiungo all'inizio
	else if (env && list->content->level > lvl)
	{
		new_env->next = list->content->next;
		list->content->next = new_env;
		return (5);
	}
	return (0);
}
