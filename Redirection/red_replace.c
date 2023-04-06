/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 07:47:27 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/04 17:55:37 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_replace_op(char *cmd, int *ind)
{
	cmd[*ind] = 31;
	if (ft_in(cmd[*ind + 1], "><"))
	{
		(*ind)++;
		cmd[*ind] = 31;
	}
	(*ind)++;
}

void	ft_replace_fd(char *cmd, int ind)
{
	if (!ind)
		return ;
	ind--;
	while (ind > 0 && ft_isdigit(cmd[ind]))
		ind--;
	if (ft_in(cmd[ind], " 0123456789"))
	{
		if (cmd[ind] == ' ')
			ind++;
		while (!ft_in(cmd[ind], "><"))
		{
			cmd[ind] = 31;
			ind++;
		}
	}
}

void	ft_quotes_replace(char *str, int *ind, char sub)
{
	if (str[*ind] == '\'')
	{
		str[*ind] = sub;
		(*ind)++;
		while (str[*ind] != '\'')
		{
			str[*ind] = sub;
			(*ind)++;
		}
	}
	else if (str[*ind] == '\"')
	{
		str[*ind] = sub;
		(*ind)++;
		while (str[*ind] != '\"')
		{
			str[*ind] = sub;
			(*ind)++;
		}
	}
}

void	ft_replace_fn(char *cmd, int *ind)
{
	while (cmd[*ind] == ' ')
	{
		cmd[*ind] = 31;
		(*ind)++;
	}
	while (cmd[*ind] && cmd[*ind] != ' ')
	{
		ft_quotes_replace(cmd, ind, 31);
		cmd[*ind] = 31;
		(*ind)++;
	}
	(*ind)--;
}

void	ft_replace_red(t_shell *shell, int n_cmd)
{
	int	i;

	i = 0;
	while (shell->parsed[n_cmd][i])
	{
		ft_quotes_check(shell->parsed[n_cmd], &i);
		if (ft_in(shell->parsed[n_cmd][i], "><"))
		{
			ft_replace_fd(shell->parsed[n_cmd], i);
			ft_replace_op(shell->parsed[n_cmd], &i);
			ft_replace_fn(shell->parsed[n_cmd], &i);
		}
		i++;
	}
}
