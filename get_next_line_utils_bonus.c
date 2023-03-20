/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 08:54:16 by gpanico           #+#    #+#             */
/*   Updated: 2023/02/01 09:16:53 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_buffer_al(int fd, char **buffer)
{
	int	i;

	if (!buffer[fd])
	{
		buffer[fd] = (char *) malloc(sizeof(char) * BUFFER_SIZE);
		if (!buffer[fd])
			return (1);
		i = 0;
		while (i < BUFFER_SIZE)
		{
			buffer[fd][i] = 0;
			i++;
		}
	}
	return (0);
}

void	ft_free_buffer(int r, int fd, char **buffer)
{
	if (!r)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
}

int	ft_fill(char **str, char **buffer, int fd)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE && buffer[fd][i] != '\n' && buffer[fd][i])
		i++;
	if (i)
	{
		*str = ft_realloc(*str, buffer[fd], i);
		if (!(*str))
			return (1);
		if (BUFFER_SIZE != 1)
			ft_movebuffer(buffer[fd], i);
	}
	return (0);
}
