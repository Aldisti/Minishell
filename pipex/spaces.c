/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:10:52 by marco             #+#    #+#             */
/*   Updated: 2023/03/19 18:39:56 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	protect_space(char *strs)
{
	char	*str;
	int		i;

	str = ft_strchr(strs, '\'');
	if (str)
	{
		i += 1;
		while (str[++i] && str[i] != '\'')
			if (str[i] == ' ')
				str[i] = '#';
	}
}

void	convert(char **strs)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	while (strs[++i])
	{
		if (ft_strchr(strs[i], '#'))
		{
			str = ft_strchr(strs[i], '#');
			j = -1;
			while (str[++j] && str[j] != '\'')
			{
				if (str[j] == '#')
					str[j] = ' ';
			}
		}
	}
}

void	r_trim(char **cmd1)
{
	int		i;
	char	*temp;

	i = -1;
	while (cmd1[++i])
	{
		if (ft_strchr(cmd1[i], '\''))
		{
			temp = ft_strtrim(cmd1[i], "\'");
			free(cmd1[i]);
			cmd1[i] = ft_strdup(temp);
			free(temp);
		}
	}
}
