/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:32:08 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/18 13:44:01 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	ft_check_error(int r, char *str)
{
	if (r < 0)
	{
		if (str)
			free(str);
		return (1);
	}
	return (0);
}

void	ft_movebuffer(char *buffer)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE - 1)
	{
		buffer[i] = buffer[i + 1];
		if (!buffer[i])
			break ;
		i++;
	}
	buffer[i] = 0;
}

char	*ft_realloc_get(char *str, char *buffer)
{
	char	*new;

	if (!str)
	{
		new = (char *) malloc(2 * sizeof(char));
		if (!new)
			return (NULL);
		new[0] = buffer[0];
		new[1] = 0;
	}
	else
	{
		new = ft_strjoin(str, buffer);
		if (str)
			ft_free((void **)&str);
	}
	ft_movebuffer(buffer);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*str;
	int			r;

	r = 1;
	str = NULL;
	while (r)
	{
		while (buffer[0] != '\n' && buffer[0])
		{
			str = ft_realloc_get(str, buffer);
			if (!str)
				return (NULL);
		}
		if (buffer[0] == '\n')
		{
			str = ft_realloc_get(str, buffer);
			break ;
		}
		r = read(fd, buffer, BUFFER_SIZE);
		if (ft_check_error(r, str))
			return (NULL);
	}
	return (str);
}
