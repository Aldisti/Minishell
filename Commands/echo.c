/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:25:57 by afraccal          #+#    #+#             */
/*   Updated: 2023/04/12 11:27:47 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_arg(char **cmd, int i)
{
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
}

int	echo(char **argv)
{
	int		i;
	int		flag;
	char	**cmd;

	i = 1;
	cmd = line_filter(argv);
	if (!cmd[i])
	{
		printf("\n");
		return (0);
	}
	if (!ft_strncmp(cmd[i], "-n", 2))
	{
		flag = 0;
		i++;
	}
	else
		flag = 1;
	print_arg(cmd, i);
	if (flag == 0)
		return (0);
	else
		printf("\n");
	return (0);
}
