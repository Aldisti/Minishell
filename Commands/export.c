/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:16:39 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/13 15:01:45 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	ft_print_export(t_shell *shell, int lvl)
{
	t_list	*lst;
	t_env	*tmp;
	char	*str;

	lst = shell->list;
	while (lst)
	{
		tmp = lst->content;
		while (tmp && tmp->next && tmp->next->level <= lvl)
			tmp = tmp->next;
		str = ft_strtrim(tmp->value, "\"");
		ft_free((void **)&(tmp->value));
		tmp->value = str;
		if (tmp && tmp->name && tmp->value && tmp->level <= lvl)
			printf("declare -x %s\"%s\"\n", tmp->name, tmp->value);
		else if (tmp && tmp->name && !tmp->value && tmp->level <= lvl)
		{
			tmp->name[ft_strlen(tmp->name) - 1] = 0;
			printf("declare -x %s\n", tmp->name);
			tmp->name[ft_strlen(tmp->name)] = '=';
		}
		lst = lst->next;
	}
	return (0);
}

int	ft_export(t_shell *shell, char **cmd, int lvl)
{
	t_env	*new_env;
	t_list	*list;
	char	*name;
	char	*value;

	if (!cmd[1])
		return (ft_print_export(shell, lvl));
	if (shell->n_cmds != 1)
		return (0);
	while (++cmd && *cmd)
	{
		ft_remove_quotes(shell, cmd);
		ft_set_name_value(shell, &name, &value, *cmd);
		new_env = ft_env_new(name, value, lvl);
		if (!new_env)
			ft_die(shell, 1, 12);
		list = ft_get_node(shell->list, name);
		ft_do_export1(shell, list, &new_env, lvl);
	}
	return (0);
}
