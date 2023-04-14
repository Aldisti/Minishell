/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:47:23 by mpaterno          #+#    #+#             */
/*   Updated: 2023/04/14 14:08:53 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
	int	is_number(char *str)

	check if a given string is a number
	or not, by calling ft_isdigit on each char
*/
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

/*
	int	ft_exit_single(t_shell *shell, char **cmd)

	do the right thing with exit if the command is
	called alone without other commands, checking the cases:

	1. exit (more than 2 args)
	2. exit (1 args)
	making different actions whatever the first arguments is a number
	or a string
*/
int	ft_exit_single(t_shell *shell, char **cmd)
{
	if (args_count(cmd) > 2)
	{
		if (!is_number(cmd[1]))
		{
			write(2, "exit\nexit: numeric argument required\n", 38);
			ft_die(shell, 1, 255);
		}
		else if (is_number(cmd[1]))
			return (write(2, "exit\nexit: too many arguments\n", 31) * 0 + 1);
	}
	else if (args_count(cmd) > 1)
	{
		if (is_number(cmd[1]))
		{
			write(2, "exit\n", 5);
			ft_die(shell, 1, (unsigned char) ft_atoi(cmd[1]));
		}
		else if (!is_number(cmd[1]))
		{
			write(2, "exit\nexit: numeric argument required\n", 38);
			ft_die(shell, 1, (unsigned char) ft_atoi(cmd[1]));
		}
	}
	return (0);
}

/*
	int	ft_exit_pipes(char **cmd)

	do the right thing with exit if the command is 
	placed in commands linked with pipe testind different cases:

	1. exit (more than 2 args)
	2. exit (1 args)
	making different actions whatever the first arguments is a number
	or a string
*/
int	ft_exit_pipes(char **cmd)
{
	if (args_count(cmd) > 2)
	{
		if (!is_number(cmd[1]))
			return (write(2, "exit: numeric argument required\n", 33) * 0 + 255);
		else if (is_number(cmd[1]))
			return (write(2, "exit: too many arguments\n", 26) * 0 + 1);
	}
	else if (args_count(cmd) > 1)
	{
		if (is_number(cmd[1]))
			return (ft_atoi(cmd[1]));
		else if (!is_number(cmd[1]))
			return (write(2, "exit: numeric argument required\n", 32) * 0 + 255);
	}
	return (0);
}

/*
	int	ft_exit(t_shell *shell, char **cmd)

	this func simply works as selector for different 
	cases here the func test if exit is paseed as single
	command and if so check if is alone or in a pipe
	then split the situation in 2 cases:
	
	1. more than 1 command chained with exit
	2. no command chained with exit
*/
int	ft_exit(t_shell *shell, char **cmd)
{
	unsigned char	val;

	val = 0;
	if (args_count(cmd) == 1 && shell->pipex.cmd_count == 1)
		ft_die(shell, 1, 0);
	else if (args_count(cmd) == 1 && shell->pipex.cmd_count > 1)
		return (0);
	if (shell->pipex.cmd_count > 1)
		val = ft_exit_pipes(cmd);
	else if (shell->pipex.cmd_count == 1)
		val = ft_exit_single(shell, cmd);
	return ((int) val);
}
