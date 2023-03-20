/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:32:03 by mpaterno          #+#    #+#             */
/*   Updated: 2023/01/20 09:31:02 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new_str;

	i = -1;
	if (!str || !(*f))
		return (0);
	new_str = ft_strdup(str);
	if (!new_str)
		return (0);
	while (str[++i])
		new_str[i] = f(i, str[i]);
	return (new_str);
}
