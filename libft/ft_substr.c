/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:32:49 by mpaterno          #+#    #+#             */
/*   Updated: 2023/01/20 15:10:14 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;

	i = 0;
	if (!str || start > ft_strlen(str))
		return (ft_strdup(""));
	new_str = malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (0);
	ft_bzero(new_str, len + 1);
	while (i < len && str[start])
		new_str[i++] = str[start++];
	new_str[i] = 0;
	return (new_str);
}
