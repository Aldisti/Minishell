/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:16:39 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/04 11:16:07 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

t_list	*ft_go_before(t_list *list, const char *name)
{
	if (!list || !name)
		return (0);
	while (list->next && ft_strcmp(list->next->content->name, name) > 0)
		list = list->next;
	return (list);
}

int	ft_export(t_shell *shell, char **cmd, int lvl)
{
	t_list	*list_tmp;
	t_env	*env_tmp;

	// if (!cmd[1])
	// 	return (ft_print_export(shell, cmd, lvl));
	list_tmp = ft_go_before(shell->list, "HOME");
	printf("name: %s\nvalue: %s\n", list_tmp->content->name, list_tmp->content->value);
	return (0);
}
