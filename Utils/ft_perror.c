/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:30:26 by mpaterno          #+#    #+#             */
/*   Updated: 2023/04/14 15:06:51 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	ft_perror(const char *str, char *arg)
{
	int	len;
	int	len2;

	len = ft_strlen(str);
	len2 = ft_strlen(arg);
	write(2, "\033[31m", 6);
	if (arg)
		write(2, arg, len2);
	write(2, str, len);
	write(2, "\033[0m", 5);
	return (len + len2);
}
