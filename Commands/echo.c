/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:25:57 by afraccal          #+#    #+#             */
/*   Updated: 2023/04/12 22:27:49 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_arg(char **cmd, int i, int flag)
{
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (flag == 0)
		return ;
	else
		printf("\n");
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
		ft_free_mat((void ***) &cmd);
		return (0);
	}
	if (!ft_strncmp(cmd[i], "-n", 2))
	{
		flag = 0;
		i++;
		while (cmd[i] && !ft_strncmp(cmd[i], "-n", 2))
			i++;
	}
	else
		flag = 1;
	print_arg(cmd, i, flag);
	ft_free_mat((void ***) &cmd);
	return (0);
}
