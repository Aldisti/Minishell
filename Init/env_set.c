/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:48:26 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/06 16:15:32 by adi-stef         ###   ########.fr       */
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
		elem = (t_env *)ft_calloc(sizeof(t_env), 1);
		if (!elem)
			exit(1); // ft_die(); Error: memory error
		elem->set = 1;
		elem->name = ft_get_name(envp[i]);
		elem->value = ft_get_value(envp[i], elem->name, 1);
		if (!elem->name || !elem->value)
			exit(1); // ft_die(); Error: memory error
		elem->level = 0;
		list_elem = ft_lstnew((void *)elem);
		if (!list_elem)
			exit(1); // ft_die(); Error: memory error
		ft_lst_insert(&list, list_elem);
		i++;
	}
	return (list);
}
