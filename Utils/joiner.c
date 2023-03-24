/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joiner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:39:38 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/24 10:57:51 by adi-stef         ###   ########.fr       */
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
		if (n)
		{
			if (tab[i])
				free(tab[i]);
			if (out)
				free(out);
			tab[i] = 0;
			out = 0;
		}
		out = tmp;
	}
	return (tmp);
}