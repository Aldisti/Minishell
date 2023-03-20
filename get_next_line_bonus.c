/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:32:08 by gpanico           #+#    #+#             */
/*   Updated: 2023/02/01 09:29:44 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_check_error(int r, char *str, char *buffer)
{
	if (r < 0)
	{
		if (str)
			free(str);
		if (buffer)
			free(buffer);
		return (1);
	}
	return (0);
}

char	*ft_strjoin(char *str, char *buffer, int step)
{
	int		len;
	char	*new;

	len = 0;
	while (str[len])
		len++;
	new = (char *) malloc((len + step + 1) * sizeof(char));
	if (!new)
	{
		if (str)
			free(str);
		return (NULL);
	}
	new[len + step] = 0;
	while (--step >= 0)
		new[len + step] = buffer[step];
	while (--len >= 0)
		new[len] = str[len];
	if (str)
		free(str);
	return (new);
}

void	ft_movebuffer(char *buffer, int step)
{
	int	i;

	i = 0;
	if (!step)
		return ;
	while (i < BUFFER_SIZE)
	{
		if (!buffer[i])
			break ;
		if (i < BUFFER_SIZE - step)
			buffer[i] = buffer[i + step];
		else
			buffer[i] = 0;
		i++;
	}
}

char	*ft_realloc(char *str, char *buffer, int step)
{
	char	*new;
	int		i;

	if (!step)
		return (str);
	if (!str)
	{
		new = (char *) malloc((step + 1) * sizeof(char));
		if (!new)
			return (NULL);
		i = 0;
		while (i < step)
		{
			new[i] = buffer[i];
			i++;
		}
		new[i] = 0;
	}
	else
		new = ft_strjoin(str, buffer, step);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*str;
	int			r;

	r = 1;
	str = NULL;
	if (ft_buffer_al(fd, buffer))
		return (NULL);
	while (r)
	{
		if (ft_fill(&str, buffer, fd))
			return (NULL);
		if (buffer[fd][0] == '\n')
		{
			str = ft_realloc(str, buffer[fd], 1);
			ft_movebuffer(buffer[fd], 1);
			break ;
		}
		r = read(fd, buffer[fd], BUFFER_SIZE);
		if (ft_check_error(r, str, buffer[fd]))
			return (NULL);
	}
	ft_free_buffer(r, fd, buffer);
	return (str);
}
