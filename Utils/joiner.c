/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joiner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:39:38 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/13 11:12:08 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	description: it's like strjoin but works for n strings
//	input: tab is an array of strings and n if it's not 0 does the free of tab
char	*ft_joiner(char **tab, int n)
{
	int		i;
	char	*out;
	char	*tmp;

	i = -1;
	out = 0;
	while (tab[++i])
	{
		tmp = ft_strjoin(out, tab[i]);
		if (out)
			ft_free((void **)&out);
		if (!tmp)
			break ;
		out = tmp;
	}
	if (!n)
		return (tmp);
	i = -1;
	while (tab[++i])
		ft_free((void **)&tab[i]);
	return (tmp);
}
