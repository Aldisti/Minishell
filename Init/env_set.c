/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:48:26 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/13 11:10:38 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * Description:	Get the name (i.e. first substring terminated by '=')
 * 		from a string.
 * Input:	a string.
 * Output:	a substring ended with "=" or null byte terminated.
*/
char	*ft_get_name(const char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != ' ')
		i++;
	i++;
	name = ft_substr(str, 0, i);
	return (name);
}

/*
 * Description: Get the value (i.e. the substring following the '=' character)
 * 		from a string; if the name (see the previous function) 
 * 		is 'SHLVL' the value is incremented by one.
 * Input:	the string, the name (has to be in the string) and an integer n
 * 		(if n is equal to zero SHLVL isn't incremented).
 * Output:	the substring value.
*/
char	*ft_get_value(const char *str, const char *name, int n)
{
	int		i;
	char	*value;
	char	*tmp;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	value = ft_substr(str, i + 1, ft_strlen(str));
	if (n && !ft_strncmp(name, "SHLVL=", 7))
	{
		tmp = value;
		value = ft_itoa(ft_atoi(value) + 1);
		ft_free((void **)&tmp);
	}
	return (value);
}

void	ft_die_env(t_list *list, t_list *list_elem, t_env *elem)
{
	t_list	*tmp;

	if (elem)
	{
		ft_free((void **) &(elem->name));
		ft_free((void **) &(elem->value));
		ft_free((void **) &elem);
	}
	if (list_elem)
		ft_free((void **) &list_elem);
	while (list)
	{
		ft_free((void **) &(list->content->name));
		ft_free((void **) &(list->content->value));
		ft_free((void **) &(list->content));
		tmp = list;
		list = list->next;
		ft_free((void **) &(tmp));
	}
	exit(12);
}

/*
 * Description:	Allocate and initialize a structure (list of list)
 * 		containg all the shell variables; each list node
 * 		points to another list in order to preserver 
 * 		the subshell level where each variable is defined 
 * 		(at the begining all the variables are initiaze 
 * 		at level zero).
 * Input:	envp taken from main function.
 * Output:	the structure previously described (see Input)
 * 		with all shell variables in it.
*/
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
		list_elem = NULL;
		elem = (t_env *)ft_calloc(sizeof(t_env), 1);
		if (!elem)
			ft_die_env(list, list_elem, elem);
		elem->set = 1;
		elem->name = ft_get_name(envp[i]);
		elem->value = ft_get_value(envp[i], elem->name, 1);
		if (!elem->name || !elem->value)
			ft_die_env(list, list_elem, elem);
		list_elem = ft_lstnew((void *)elem);
		if (!list_elem)
			ft_die_env(list, list_elem, elem);
		ft_lst_insert(&list, list_elem);
		i++;
	}
	return (list);
}
