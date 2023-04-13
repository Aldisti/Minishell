/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:34:02 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/13 11:13:57 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	*ft_calloc(size_t num, size_t dim)
{
	char	*ptr;
	size_t	i;

	if ((num * dim) / dim != num)
		return (0);
	ptr = (char *) malloc (num * dim);
	if (!ptr)
		return (0);
	i = 0;
	while (i < (num * dim))
		ptr[i++] = 0;
	return ((void *)ptr);
}
