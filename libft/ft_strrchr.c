/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:00:13 by gpanico           #+#    #+#             */
/*   Updated: 2023/01/23 08:00:33 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*chr;

	chr = 0;
	i = 0;
	while (s[i])
	{
		if ((unsigned char)c == (unsigned char) s[i])
			chr = (char *) &s[i];
		i++;
	}
	if ((unsigned char)c == 0)
		return ((char *) &s[i]);
	return (chr);
}
