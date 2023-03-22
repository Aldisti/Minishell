/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:00:25 by adi-stef          #+#    #+#             */
/*   Updated: 2023/01/17 13:31:39 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ptr;

	if (!s1)
		return (0);
	ptr = malloc ((ft_strlen(s1) + 1) * sizeof (char));
	if (!ptr)
		return (0);
	i = -1;
	while (s1[++i])
		ptr[i] = s1[i];
	ptr[i] = s1[i];
	return (ptr);
}
