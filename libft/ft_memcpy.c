/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:27:44 by mpaterno          #+#    #+#             */
/*   Updated: 2023/01/16 13:27:02 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char		*ptr_src;
	char			*ptr_dst;
	size_t			i;

	if ((dst == src) || n == 0)
		return (dst);
	if (!dst && !src)
		return (0);
	i = 0;
	ptr_src = (const char *) src;
	ptr_dst = (char *) dst;
	while (i < n)
	{
		ptr_dst[i] = ptr_src[i];
		i++;
	}
	return (dst);
}
