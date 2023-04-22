/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:05:07 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/13 12:05:26 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_shell_errno;

/*
 * Description:	checks if the strings in parsed have
 * 		invalid operators.
 * Input:	the strings array.
 * Output:	returns an integer:
 * 			-0 if there are an invalid command;
 * 			-1 if there are invalid command.
*/
int	ft_valid_command(char **parsed)
{
	int	i;
	int	j;
	int	valid;

	valid = 0;
	i = 0;
	while (parsed[i])
	{
		j = 0;
		while (parsed[i][j])
		{
			if (!ft_in(parsed[i][j], " \n\t()"))
				valid = 1;
			j++;
		}
		if (!valid)
			return (0);
		valid = 0;
		i++;
	}
	return (1);
}

/*
 * Syntax error:	invalid operator, unexpected token, 
 * 					unclosed quotes/parentheses.
*/
void	*ft_die_parser(t_shell *shell, char **parsed)
{
	ft_free_mat((void ***) &parsed);
	ft_die(shell, 0, 2);
	return (NULL);
}

/*
 * Description:	checks if there are characters before parentheses.
 * Input:	the string to check.
 * Output:	returns an integer:
 * 			-0 if there aren't characters before pars;
 * 			-1 if there are.
*/
int	ft_check_beforepar(char *line)
{
	int	i;
	int	chr;
	int	flag;

	i = 0;
	chr = 0;
	flag = 0;
	while (line[i])
	{
		if (!ft_in(line[i], " ()<>|") && !flag)
			chr++;
		if (ft_in(line[i], "(") && chr)
			flag++;
		i++;
	}
	if (flag)
		return (1);
	return (0);
}

int	ft_end_op(char *line, char **parsed)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			i++;
			while (ft_in(line[i], " "))
				i++;
			if (!line[i])
			{
				fd_printf(2, "Bad Syntax: end with operator.\n");
				g_shell_errno = 2;
				ft_free_mat((void ***) &parsed);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_is_op(char *parsed, int *j)
{
	if (ft_strlen_until(&parsed[*j], " \n\t<>()") > 2)
		return (1);
	if (!ft_strncmp(&parsed[*j], "&", 1)
		&& parsed[*j + 1] != '&')
		return (1);
	if (ft_in(parsed[*j + 1], "|&")
		&& parsed[*j] != parsed[*j + 1])
		return (1);
	if (ft_in(parsed[*j + 1], "|&")
		&& parsed[*j] == parsed[*j + 1])
		(*j)++;
	return (0);
}
