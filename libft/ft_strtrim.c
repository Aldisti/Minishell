/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 08:16:22 by gpanico           #+#    #+#             */
/*   Updated: 2023/01/19 08:45:58 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_inset(const char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_tobetrimmed(const char *s1, const char *set)
{
	size_t	n;
	size_t	i;
	size_t	m;

	i = 0;
	n = 0;
	while (s1[n] && ft_inset(s1[n], set))
		n++;
	i = ft_strlen(s1);
	if (n == i)
		return (n);
	m = 0;
	while (i-- > 0 && ft_inset(s1[i], set))
		m++;
	return (n + m);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*trimmed;

	if (!set || !s1)
		return ((char *)s1);
	len = ft_strlen(s1);
	len -= ft_tobetrimmed(s1, set);
	trimmed = (char *) malloc(sizeof(char) * (len + 1));
	if (!trimmed)
		return (0);
	i = 0;
	j = 0;
	while (j < len)
	{
		while (ft_inset(s1[i], set) && j == 0)
			i++;
		trimmed[j] = s1[i];
		j++;
		i++;
	}
	trimmed[j] = 0;
	return (trimmed);
}
