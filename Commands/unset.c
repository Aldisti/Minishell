/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:21:04 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/17 11:59:51 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
DESCRIPTION
this function iterates the list and if it finds a node with no content then
will do the free of that node
*/
void	ft_clean_list(t_shell *shell)
{
	t_list	*tmp;
	t_list	*list;

	if (!(shell->list->content))
	{
		tmp = shell->list;
		shell->list = tmp->next;
		ft_free((void **)&tmp);
	}
	list = shell->list;
	while (list)
	{
		if (list->next && !(list->next->content))
		{
			tmp = list->next;
			list->next = tmp->next;
			ft_free((void **)&tmp);
		}
		if (list)
			list = list->next;
	}
}

int	ft_unset(t_shell *shell, char **cmd, int lvl)
{
	t_list	*lst;
	t_env	*env;
	t_env	*tmp;

	if (!cmd[1] || shell->n_cmds != 1)
		return (0);
	while (++cmd && *cmd)
	{
		ft_remove_quotes(shell, cmd);
		lst = ft_get_node(shell->list, *cmd);
		if (!lst)
			continue ;
		env = ft_get_env(lst, lvl);
		if (!env)
			continue ;
		tmp = ft_envfind_sort(lst->content, lvl);
		if (lst->content->level == env->level)
			lst->content = lst->content->next;
		if (tmp->next && tmp->next->level == env->level)
			tmp->next = env->next;
		ft_free_env(&env);
		ft_clean_list(shell);
	}
	return (0);
}
