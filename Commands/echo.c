/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:25:57 by afraccal          #+#    #+#             */
/*   Updated: 2023/04/11 22:32:36 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(char **argv)
{
	char	**cmd;
	int		i;
	int		flag;

	flag = 1;
	i = 1;
	cmd = argv;
	while(cmd[i])
	{
		while (!strncmp(cmd[i], "-n", 2))
		{
			flag = 0;
			i++;
		}
		printf("%s", cmd[i]);
		if(cmd[i + 1])
			printf(" ");
		i++;
	}
	if (flag == 0)
		return (0);
	else
		printf("\n");
	return (0);
}
