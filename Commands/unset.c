/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:21:04 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/08 12:35:52 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	ft_unset(t_shell *shell, char **cmd, int lvl)
{
	t_list	*lst_tmp;
	t_list	*lst;
	t_env	*env;
	t_env	*tmp;

	if (!cmd[1])
		return (0);
	while (++cmd && *cmd)
	{
		lst = ft_get_node(shell->list, *cmd);
		if (!lst)
			continue ;
		env = ft_get_env(lst, lvl);
		if (!env)
			continue ;
		tmp = lst->content;
		while (tmp && tmp->level < lvl && tmp->next && tmp->next->level != lvl)
			tmp = tmp->next;
		if (lst->content->level == env->level)
			lst->content = lst->content->next;
		if (tmp->next && tmp->next->level == env->level)
			tmp->next = env->next;
		ft_free_env(&env);
		if (!lst->content)
		{
			lst = shell->list;
			while (lst && lst->next && lst->next->content
				&& ft_strncmp(lst->next->content->name, *cmd, ft_strlen(*cmd)))
				lst = lst->next;
			lst_tmp = lst->next->next;
			ft_free((void **)&(lst->next));
			lst->next = lst_tmp;
		}
	}
	return (0);
}