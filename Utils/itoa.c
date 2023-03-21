/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:20:08 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/21 18:27:00 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_intlen(int n)
{
	int		i;

	i = 1;
	if (n < 0)
		i++;
	else if (n == 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		i;

	i = ft_intlen(n);
	ptr = ft_calloc(i, sizeof (char));
	if (!ptr)
		return (0);
	if (n < 0)
		ptr[0] = 45;
	else if (n < 10 && n >= 0)
	{
		ptr[0] = n + 48;
		return (ptr);
	}
	i--;
	while (--i >= 0 && n)
	{
		ptr[i] = ft_abs(n % 10) + 48;
		n /= 10;
	}
	return (ptr);
}
