/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:18:10 by afraccal          #+#    #+#             */
/*   Updated: 2023/04/21 16:36:50 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	env(t_shell	*shell, char **cmd, int lvl)
// {
// 	t_list	*lst;
// 	t_env	*tmp;
// 	char	*name;

// 	lst = shell->list;
// 	while (lst)
// 	{
// 	name = ft_strdup(lst->content->name);
// 	if (!name)
// 		ft_die(shell, 1, 12);
// 	if (name[ft_strlen(name) - 1] == '=')
// 		name[ft_strlen(name) - 1] = 0;
// 	tmp = ft_search_in_list(lst, name, lvl);
// 	ft_free((void **)&name);
// 	if (tmp && tmp->name && tmp->value)
// 		printf("%s%s\n", tmp->name, tmp->value);
// 	lst = lst->next;
// }
int	env(t_shell	*shell, char **cmd, int lvl)
{
	int	i;

	if (cmd[1])
	{
		fd_printf(2, "Bad Syntax: env: too many arguments\n");
		return (2);
	}
	ft_free_mat((void ***)&(shell->envp));
	shell->envp = list_convert(shell->list, lvl);
	if (!shell->envp)
		ft_die(shell, 1, 12);
	i = -1;
	while (shell->envp[++i])
		printf("%s\n", shell->envp[i]);
	return (0);
}
