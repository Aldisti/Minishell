/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:25:57 by afraccal          #+#    #+#             */
/*   Updated: 2023/04/19 16:15:48 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arg_check(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	print_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"')
			while (cmd[++i] != '\"')
				printf("%c", cmd[i]);
		else if (cmd[i] == '\'')
			while (cmd[++i] != '\'')
				printf("%c", cmd[i]);
		else
			printf("%c", cmd[i]);
		i++;
	}
}

void	print_arg(char **cmd, int i, int flag)
{
	while (cmd[i])
	{
		print_cmd(cmd[i]);
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
	if (!ft_strncmp(cmd[i], "-n", 2) && arg_check(cmd[i]))
	{
		flag = 0;
		i++;
		while (cmd[i] && !ft_strncmp(cmd[i], "-n", 2) && arg_check(cmd[i]))
			i++;
	}
	else
		flag = 1;
	print_arg(cmd, i, flag);
	ft_free_mat((void ***) &cmd);
	return (0);
}
