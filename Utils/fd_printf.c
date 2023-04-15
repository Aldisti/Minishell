/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:30:26 by mpaterno          #+#    #+#             */
/*   Updated: 2023/04/15 09:14:30 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	ft_putstr(int fd, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_selector(int fd, va_list args, int c)
{
	if (c == 's')
		return (ft_putstr(fd, va_arg(args, char *)));
	return (0);
}

int	fd_printf(int fd, const char *str, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(args, str);
	if (fd == 2)
		write(2, "\e[1;31;41m", 11);
	while (str[i])
	{
		if (str[i] == '%')
			len += ft_selector(fd, args, str[++i]);
		else
			len += write(fd, &str[i], 1);
		i++;
	}
	if (fd == 2)
		write(2, "\e[0m", 5);
	va_end(args);
	return (len);
}
