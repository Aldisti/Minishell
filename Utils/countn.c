/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countn.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:13:10 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/13 11:13:18 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	return: returns the number of occurences of c in str for n chars
//	pro tip: if n is -1 it checks all the string
int	ft_countn(const char *str, const char c, int n)
{
	int	i;

	if (n == -1)
		n = ft_strlen(str);
	i = 0;
	while (str++ && n > 0)
	{
		if (*str == c)
			i++;
		n--;
	}
	return (i);
}
