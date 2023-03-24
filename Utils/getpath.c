/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afraccal <afraccal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:38:07 by afraccal          #+#    #+#             */
/*   Updated: 2023/03/24 15:59:57 by afraccal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path(char **env)
{
	char	*path;
	int		i;
	int		j;

	i = -1;
	path = malloc(sizeof(char) * 1);
	path[0] = '\0';
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			j = 3;
			while (env[i][++j])
				path = ft_strjoin(path, env[i][j]);
			break ;
		}
	}
	return (path);
}