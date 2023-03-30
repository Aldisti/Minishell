/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:24:37 by marco             #+#    #+#             */
/*   Updated: 2023/03/19 21:18:23 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

char	*pwd(void)
{
	char	*str;
	size_t	size;

	size = 20;
	str = malloc(sizeof(char) * size);
	if (!str)
		return (0);
	while (getcwd(str, size) == 0)
	{
		if (errno == ERANGE)
		{
			free(str);
			str = 0;
			size *= 2;
			str = malloc(sizeof(char) * size);
			if (!str)
				return (0);
		}
	}
	return (str);
}


void    print_pwd()
{   
    char *str;

    str = pwd();
    printf("%s\n", str);
    free(str);
}