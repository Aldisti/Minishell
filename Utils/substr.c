/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:57:07 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/07 08:55:21 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*ptr;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s) - start;
	ptr = (char *) malloc ((len + 1) * sizeof (char));
	if (!ptr)
		return (0);
	i = 0;
	while (len-- > 0 && s[start])
		ptr[i++] = s[start++];
	ptr[i] = 0;
	return (ptr);
}
