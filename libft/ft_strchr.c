/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:26:56 by gpanico           #+#    #+#             */
/*   Updated: 2023/01/23 07:59:22 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if ((unsigned char) c == (unsigned char)s[i])
			return ((char *) &s[i]);
		i++;
	}
	if ((unsigned char) c == 0)
		return ((char *) &s[i]);
	return (0);
}
