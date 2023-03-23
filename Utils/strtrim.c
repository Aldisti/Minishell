/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:11:58 by adi-stef          #+#    #+#             */
/*   Updated: 2023/01/22 13:39:03 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_inset(char chr, char const *set)
{
	while (*set)
		if (*set++ == chr)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		i;
	int		j;
	int		k;

	if (!s1)
		return (0);
	i = 0;
	while (ft_inset(s1[i], set) && s1[i])
		i++;
	j = ft_strlen(s1) - 1;
	if (i == j)
		return (0);
	while (ft_inset(s1[j], set) && j > i)
		j--;
	ptr = (char *) malloc (((j - i) + 2) * sizeof (char));
	if (!ptr)
		return (0);
	k = 0;
	while (i <= j)
		ptr[k++] = s1[i++];
	ptr[k] = 0;
	return (ptr);
}