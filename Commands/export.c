/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:16:39 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/05 18:42:12 by adi-stef         ###   ########.fr       */
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
	int	i;

	ft_free_mat((void ***)&(shell->envp));
	shell->envp = list_convert(shell->list, lvl);
	if (!shell->envp)
		return (0);
	i = 0;
	while (shell->envp[i])
		printf("declare -x %s\n", shell->envp[i++]);
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

	if (!cmd[1])
		return (ft_print_export(shell, lvl));
	name = ft_get_name(cmd[1]);
	value = ft_get_value(cmd[1], name, 0);
	if (!name || (!value && ft_strchr(cmd[1], '=')))
	{
		ft_free((void **)&name);
		ft_free((void **)&value);
		return (-1);
	}
	list = shell->list;
	while (list && ft_strcmp(list->content->name, name))
		list = list->next;
	// ft_print_list_node(list);
	if (!new_env)
	{
		ft_free((void **)&name);
		ft_free((void **)&value);
		return (-2);
	}
	new_env = ft_env_new(name, value, lvl);
	if (!list)
	{
		new_lst = ft_lstnew(new_env);
		if (!new_lst)
			return (ft_free_env(&new_env));
		ft_lst_insert(&(shell->list), new_lst);
		return (1);
	}
	env = ft_search_in_list(list, name, lvl);
	// printf("env->level: %d\n", env->level);
	// modifico solo value
	printf("2\n");
	if (env && env->level == lvl)
	{
		ft_free((void **)&(env->value));
		env->value = ft_strdup(value);
		ft_free_env(&new_env);
		return (2);
	}
	// aggiungo alla fine
	printf("4\n");
	if (env && env->level < lvl && !env->next)
	{
		env->next = new_env;
		return (4);
	}
	// aggiungo in mezzo
	printf("3\n");
	if (env && env->level < lvl && env->next->level > lvl)
	{
		new_env->next = env->next;
		env->next = new_env;
		return (3);
	}
	// aggiungo all'inizio
	printf("5\n");
	if (env && list->content->level > lvl)
	{
		new_env->next = list->content->next;
		list->content->next = new_env;
		return (5);
	}
	// printf("name: %s\nvalue: %s\n", list->content->name, list->content->value);
	return (0);
}
