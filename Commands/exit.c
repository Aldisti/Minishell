/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:47:23 by mpaterno          #+#    #+#             */
/*   Updated: 2023/04/13 16:38:35 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}


int	ft_exit(t_shell *shell, char **cmd)
{
	if (args_count(cmd) > 2 && shell->pipex.cmd_count == 1)
	{
		if (!is_number(cmd[1]))
		{
			write(2, "exit\nexit: too many arguments\n", 31);
			ft_die(shell, 1, 255);
		}
		else if (is_number(cmd[1]))
			return (write(2, "exit\nexit: too many arguments\n", 31) * 0 + 1);
	}
	else if (args_count(cmd) > 2 && shell->pipex.cmd_count > 1)
		return (write(2, "exit\nexit: too many arguments\n", 31) * 0 + 1);
	else if (args_count(cmd) > 1 && shell->pipex.cmd_count == 1)
	{
		if (is_number(cmd[1]))
			ft_die(shell, 1, ft_atoi(cmd[1]));
		else if (!is_number(cmd[1]))
			ft_die(shell, 1, 255);
	}
	else if (args_count(cmd) > 1 && shell->pipex.cmd_count > 1)
	{
		if (is_number(cmd[1]))
			return (ft_atoi(cmd[1]));
		else if (!is_number(cmd[1]))
			return (255);
	}
	else if (args_count(cmd) == 1 && shell->pipex.cmd_count > 1)
		return (0);
	else if (args_count(cmd) == 1 && shell->pipex.cmd_count == 1)
		ft_die(shell, 1, 0);
	return (0);
}