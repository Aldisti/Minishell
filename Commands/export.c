/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:16:39 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/14 14:38:40 by adi-stef         ###   ########.fr       */
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

void	ft_help_to_print(char *s1, char *s2, char *s3, char *s4)
{
	if (s1)
		write(2, s1, ft_strlen(s1));
	if (s2)
		write(2, s2, ft_strlen(s2));
	if (s3)
		write(2, s3, ft_strlen(s3));
	if (s4)
		write(2, s4, ft_strlen(s4));
}

int	ft_check_input(char *cmd, char **name, char **value, int *error)
{
	if ((!(*name) || !ft_strcmp(*name, "=")) && !ft_in('=', cmd))
	{
		ft_help_to_print("export: `': not a valid identifier\n", 0, 0, 0);
		*error = ft_free_a(name, 1) + ft_free_a(value, 0);
		return (1);
	}
	else if ((!(*name) || !ft_strcmp(*name, "=")) && ft_in('=', cmd))
	{
		ft_help_to_print("export: `", *name,
			*value, "': not a valid identifier\n");
		*error = ft_free_a(name, 1) + ft_free_a(value, 0);
		return (1);
	}
	else if (ft_isdigit((*name)[0]))
	{
		if (!(*value))
			(*name)[ft_strlen(*name) - 1] = 0;
		ft_help_to_print("export: `", *name,
			*value, "': not a valid identifier\n");
		*error = ft_free_a(name, 1) + ft_free_a(value, 0);
		return (1);
	}
	return (0);
}

int	ft_export(t_shell *shell, char **cmd, int lvl)
{
	t_env	*new_env;
	char	*name;
	char	*value;
	int		error;

	if (!cmd[1])
		return (ft_print_export(shell, lvl));
	if (shell->n_cmds != 1)
		return (0);
	error = 0;
	while (++cmd && *cmd)
	{
		ft_remove_quotes(shell, cmd);
		ft_set_name_value(shell, &name, &value, *cmd);
		if (ft_check_input(*cmd, &name, &value, &error))
			continue ;
		new_env = ft_env_new(name, value, lvl);
		if (!new_env)
			ft_die(shell, 1, 12);
		ft_do_export1(shell, &new_env, name, lvl);
	}
	return (error);
}
