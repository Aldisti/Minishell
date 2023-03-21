/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 08:03:13 by gpanico           #+#    #+#             */
/*   Updated: 2023/01/19 15:21:29 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new;
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new = (char *) malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!new)
		return (0);
	i = 0;
	while (i < len_s1 + len_s2)
	{
		if (i < len_s1)
			new[i] = s1[i];
		else
			new[i] = s2[i - len_s1];
		i++;
	}
	new[i] = 0;
	return (new);
}
