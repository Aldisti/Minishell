/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afraccal <afraccal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:25:57 by afraccal          #+#    #+#             */
/*   Updated: 2023/03/28 17:00:18 by afraccal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **argv)
{
	char	**cmd;
	int		i;
	int		flag;

	flag = 1;
	i = 1;
	cmd = ft_split(argv[0], ' ');
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
		return ;
	else
		printf("\n");
}