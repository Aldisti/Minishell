/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_strs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:03:36 by mpaterno          #+#    #+#             */
/*   Updated: 2023/03/22 16:05:37 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	trim_strs(char **strs)
{
	char	*temp;
	int		i;

	i = -1;
	while (strs[++i])
	{
		temp = ft_strtrim(strs[i], "\"\'");
		free(strs[i]);
		strs[i] = ft_strdup(temp);
		free(temp);
	}
}
