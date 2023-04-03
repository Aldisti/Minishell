/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 07:46:56 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/03 07:46:57 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_valid_red_op(char *line)
{
	if (!ft_in(*(line + 1), "><"))
		return (1);
	else if (ft_in(*(line + 2), "><"))
		return (0);
	else if (*(line) == *(line + 1))
		return (1);
	else
		return (0);
}

int	ft_red_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		ft_quotes_check(line, &i);
		if (ft_in(line[i], "><"))
		{
			if (!ft_valid_red_op(&line[i]))
				return (1); // Invalid operator
			while (ft_in(line[i], ">< "))
				i++;
			if (!line[i] || ft_in(line[i], "><"))
				return (1); // Unexpected token
		}
		i++;
	}
	return (0);
}	

int	ft_check_space(char *line, int ind)
{
	if (line[ind] == ' ' && ft_in(line[ind + 1], "><"))
		return (1);
	return (0);
}

int	ft_check_fn_status(t_shell *shell, int n_cmd, char type)
{
	if (type == 'o')
	{
		if (!shell->red.outfiles[n_cmd / 2])
			return (1);
	}
	else if (type == 'a')
	{
		if (!shell->red.afiles[n_cmd / 2])
			return (1);
	}
	else
	{
		if (!shell->red.infiles[n_cmd / 2])
			return (1);
	}
	return (0);
}
