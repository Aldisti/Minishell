/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_convert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:47:17 by mpaterno          #+#    #+#             */
/*   Updated: 2023/04/13 10:40:23 by adi-stef         ###   ########.fr       */
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
	char	*ret;

	tmp = list->content;
	while (tmp && tmp->next && tmp->next->level <= lvl)
		tmp = tmp->next;
	ret = ft_strjoin(tmp->name, tmp->value);
	if (!ret)
		return (0);
	return (ret);
	return (0);
}

char	**list_convert(t_list *list, int lvl)
{
	t_list	*temp;
	char	**ret;
	int		i;

	i = -1;
	temp = list;
	ret = (char **) malloc(sizeof(char *) * (get_lenght(list) + 1));
	if (!ret)
		return (0);
	while (temp)
	{
		if (temp && temp->content && temp->content->level <= lvl
			&& temp->content->value)
		{
			ret[++i] = get_list_line(temp, lvl);
			if (!ret[i])
				return (0);
		}
		temp = temp->next;
	}
	ret[++i] = 0;
	return (ret);
}
