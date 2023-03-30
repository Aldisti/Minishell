/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afraccal <afraccal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:48:26 by gpanico           #+#    #+#             */
/*   Updated: 2023/03/27 10:59:57 by afraccal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_name(const char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	name = ft_substr(str, 0, i);
	return (name);
}

char	*ft_get_value(const char *str)
{
	int		i;
	char	*value;

	i = 0;
	while (str[i] != '=')
		i++;
	value = ft_substr(str, i + 1, ft_strlen(str));
	return (value);
}

t_list	*ft_env_set(char **envp)
{
	int		i;
	t_list	*list;
	t_list	*list_elem;
	t_env	*elem;

	i = 0;
	list = NULL;
	while (envp[i])
	{
		elem = (t_env *)ft_calloc(sizeof(t_env), 1);
		if (!elem)
			exit(1); // ft_die(); Error: memory error
		elem->set = 1;
		elem->name = ft_get_name(envp[i]);
		elem->value = ft_get_value(envp[i]);
		if (!elem->name || !elem->value)
			exit(1); // ft_die(); Error: memory error
		list_elem = ft_lstnew((void *)elem);
		if (!list_elem)
			exit(1); // ft_die(); Error: memory error
		ft_lstadd_back(&list, list_elem);
		i++;
	}
	return (list);
}
