/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:27:12 by mpaterno          #+#    #+#             */
/*   Updated: 2023/01/20 15:41:09 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	unsigned char	*src_ptr;
	size_t			i;

	i = -1;
	src_ptr = (unsigned char *) src;
	while (++i < n)
	{
		if (src_ptr[i] == (unsigned char) c)
			return ((void *)(src + i));
	}
	return (0);
}
