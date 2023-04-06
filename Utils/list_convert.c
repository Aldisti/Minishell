/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_convert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:47:17 by mpaterno          #+#    #+#             */
/*   Updated: 2023/04/06 14:46:45 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	get_lenght(t_list *list)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = list;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

char	*get_list_line(t_list *list, int lvl)
{
	t_env	*tmp;
	char	*s1;
	char	*s2;
	char	*ret;

	if (list && list->content)
	{
		tmp = ft_search_in_list(list, list->content->name, lvl);
		s1 = tmp->name;
		s2 = tmp->value;
		if (!s2)
			s2 = "(null)";
		ret = ft_strjoin(s1, s2);
		if (!ret)
			return (0);
		return (ret);
	}
	return (0);
}

char	**list_convert(t_list *list, int lvl)
{
	t_list	*temp;
	t_env	*tmp;
	char	**ret;
	int		i;

	i = -1;
	temp = list;
	ret = (char **) malloc(sizeof(char *) * (get_lenght(list) + 1));
	if (!ret)
		return (0);
	while (temp)
	{
		if (temp && temp->content)
		{
			tmp = ft_search_in_list(temp, temp->content->name, lvl);
			if (tmp && tmp->value)
			{
				ret[++i] = get_list_line(temp, lvl);
				if (!ret)
					return (0);
			}
		}
		temp = temp->next;
	}
	ret[++i] = 0;
	return (ret);
}
