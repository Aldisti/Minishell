/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:12:11 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/08 09:59:04 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

t_env	*ft_envfind_sort(t_env *env, int lvl);
void	ft_env_insert(t_env **env, t_env *new);
void	ft_envadd_front(t_env **env, t_env *new);

int	ft_print_export(t_shell *shell, int lvl)
{
	t_list	*lst;
	t_env	*tmp;

	lst = shell->list;
	while (lst)
	{
		tmp = lst->content;
		while (tmp && tmp->next && tmp->next->level <= lvl)
			tmp = tmp->next;
		if (tmp && tmp->name && tmp->value && tmp->level <= lvl)
			printf("declare -x %s%s\n", tmp->name, tmp->value);
		else if (tmp && tmp->name && !tmp->value && tmp->level <= lvl)
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
	// t_env	*env;

	(*name) = ft_get_name(cmd);
	if (!(*name))
		ft_die(shell, 1, 12);
	// env = ft_search_in_list(shell->list, *name, 0);
	if ((*name)[ft_strlen(*name) - 1] != '=')
	{
		(*value) = ft_strjoin(*name, "=");
		if (!(*value))
			ft_die(shell, 1, 12);
		ft_free((void **)name);
		(*name) = (*value);
		(*value) = 0;
	}
	else
	{
		(*value) = ft_get_value(cmd, (*name), 0);
		if (!(*value))
		{
			ft_free((void **)name);
			ft_die(shell, 1, 12);
		}
		ft_remove_quotes(value);
	}
}

int	ft_export(t_shell *shell, t_env *new_env, char **cmd, int lvl)
{
	char	*name;
	char	*value;
	t_env	*env;
	t_list	*list;

	if (!cmd[1])
		ft_print_export(shell, lvl);
	while (++cmd && *cmd)
	{
		ft_set_name_value(shell, &name, &value, *cmd);
		list = ft_get_node(shell->list, name);
		new_env = ft_env_new(name, value, lvl);
		if (!new_env)
			ft_die(shell, 1, 12);
		if (!list)
		{
			list = ft_lstnew(new_env);
			if (!list)
				ft_die(shell, ft_free_env(&new_env) + 1, 12);
			ft_lst_insert(&(shell->list), list);
			continue ;
		}
		if (list->content && list->content->level > lvl)
		{
			new_env->next = list->content;
			list->content = new_env;
			continue ;
		}
		env = ft_get_env(list, lvl);
		if (!env)
			ft_env_insert(&(list->content), new_env);
		else
		{
			while (env && env->next && env->level != lvl)
				env = env->next;
			if (!env || env->level != lvl)
				perror("There is a problem\n");
			if (new_env->value)
			{
				ft_free((void **)&(env->value));
				env->value = ft_strdup(new_env->value);
				continue ;
			}
			ft_free_env(&new_env);
		}
	}
	return (1);
}