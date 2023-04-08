/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 19:05:43 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/08 19:15:53 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	ft_clean_level(t_shell *shell, int lvl)
{
	t_list	*lst;
	t_env	*env;
	t_env	*tmp;

	lst = shell->list;
	while (lst)
	{
		env = lst->content;
		while (env && env->next && env->next->level < lvl)
			env = env->next;
		if (env->next && env->next->level == lvl)
		{
			tmp = env->next;
			env->next = tmp->next;
			ft_free_env(&tmp);
		}
		lst = lst->next;
	}
}

void	ft_clean_from_lvl(t_shell *shell, int lvl)
{
	t_list	*lst;
	t_env	*env;
	t_env	*tmp;

	lst = shell->list;
	while (lst)
	{
		env = lst->content;
		while (env && env->next && env->next->level < lvl)
			env = env->next;
		if (env->next && env->next->level >= lvl)
		{
			tmp = env->next;
			env->next = NULL;
			while (tmp)
			{
				env = tmp->next;
				ft_free_env(&tmp);
				tmp = env;
			}
		}
		lst = lst->next;
	}
}