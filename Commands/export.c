/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:16:39 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/07 12:40:04 by gpanico          ###   ########.fr       */
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

void	ft_set_name_value(t_shell *shell, char **name, char **value, char *cmd)
{
	t_env	*env;

	(*name) = ft_get_name(cmd);
	if (!(*name))
		return ;
	env = ft_search_in_list(shell->list, *name, 0);
	if ((*name)[ft_strlen(*name) - 1] != '=')
	{
		(*value) = ft_strjoin(*name, "=");
		ft_free((void **)name);
		(*name) = (*value);
		(*value) = 0;
		if (env)
			(*value) = ft_strdup("");
	}
	else
	{
		(*value) = ft_get_value(cmd, (*name), 0);
		if (!(*value))
		{
			ft_free((void **)name);
			return ;
		}
		ft_remove_quotes(value);
	}
}

int	ft_check_var(t_shell *shell, t_env *new_env, char *cmd)
{
	t_env	*env;

	if (ft_in('=', cmd))
		return (1);
	env = ft_search_in_list(shell->list, cmd, 0);
	if (env)
	{
		ft_free_env(&new_env);
		return (0);
	}
	return (1);
}

int	ft_export(t_shell *shell, char **cmd, int lvl)
{
	t_list	*list;
	t_env	*new_env;
	char	*strs[2];

	if (!cmd[1])
		return (ft_print_export(shell, lvl));
	while (++cmd && *cmd)
	{
		ft_set_name_value(shell, &strs[0], &strs[1], *cmd);
		list = ft_get_list_node(shell->list, strs[0]);
		new_env = ft_env_new(strs[0], strs[1], lvl);
		if (!new_env)
			return (-2);
		if (!ft_check_var(shell, new_env, *cmd))
			continue ;
		if (!list)
		{
			list = ft_lstnew(new_env);
			if (!list)
				return (ft_free_env(&new_env));
			ft_lst_insert(&(shell->list), list);
		}
		else
			ft_if1(list, new_env);
	}
	return (1);
}
