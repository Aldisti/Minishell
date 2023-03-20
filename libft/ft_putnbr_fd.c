/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:28:19 by mpaterno          #+#    #+#             */
/*   Updated: 2023/01/16 12:28:19 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		temp;
	char	c;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			n = -n;
			write(fd, "-", 1);
		}
		if (n <= 9)
		{
			c = n + '0';
			write(fd, &c, 1);
		}
		else
		{
			temp = (n % 10) + '0';
			n = n / 10;
			ft_putnbr_fd(n, fd);
			write(fd, &temp, 1);
		}
	}
}
