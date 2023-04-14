/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:16:39 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/14 13:50:33 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

extern int	g_shell_errno;

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

int	ft_check_input(char *cmd, char **name, char **value)
{
	if ((!(*name) || !ft_strcmp(*name, "=")) && !ft_in('=', cmd))
	{
		write(2, "export: `': not a valid identifier\n", 35);
		g_shell_errno = ft_free_a(name, 1) + ft_free_a(value, 0);
		return (1);
	}
	else if ((!(*name) || !ft_strcmp(*name, "=")) && ft_in('=', cmd))
	{
		write(2, "export: `", 9);
		write(2, *name, ft_strlen(*name));
		write(2, *value, ft_strlen(*value));
		write(2, "': not a valid identifier\n", 26);
		g_shell_errno = ft_free_a(name, 1) + ft_free_a(value, 0);
		return (1);
	}
	return (0);
}

int	ft_export(t_shell *shell, char **cmd, int lvl)
{
	t_env	*new_env;
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
		if (ft_check_input(*cmd, &name, &value))
			continue ;
		new_env = ft_env_new(name, value, lvl);
		if (!new_env)
			ft_die(shell, 1, 12);
		ft_do_export1(shell, &new_env, name, lvl);
	}
	return (0);
}
